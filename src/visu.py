
import numpy as np
import matplotlib.pyplot as plt
import sys

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
from matplotlib.patches import Polygon

from matplotlib import widgets


class Quaternion:
	"""Quaternion Rotation:

	Class to aid in representing 3D rotations via quaternions.
	"""
	@classmethod
	def from_v_theta(cls, v, theta):
		"""
		Construct quaternions from unit vectors v and rotation angles theta

		Parameters
		----------
		v : array_like
			array of vectors, last dimension 3. Vectors will be normalized.
		theta : array_like
			array of rotation angles in radians, shape = v.shape[:-1].

		Returns
		-------
		q : quaternion object
			quaternion representing the rotations
		"""
		theta = np.asarray(theta)
		v = np.asarray(v)
		s = np.sin(0.5 * theta)
		c = np.cos(0.5 * theta)

		v = v * s / np.sqrt(np.sum(v * v, -1))
		x_shape = v.shape[:-1] + (4,)

		x = np.ones(x_shape).reshape(-1, 4)
		x[:, 0] = c.ravel()
		x[:, 1:] = v.reshape(-1, 3)
		x = x.reshape(x_shape)

		return cls(x)

	def __init__(self, x):
		self.x = np.asarray(x, dtype=float)

	def __repr__(self):
		return "Quaternion:\n" + self.x.__repr__()

	def __mul__(self, other):
		# multiplication of two quaternions.
		# we don't implement multiplication by a scalar
		sxr = self.x.reshape(self.x.shape[:-1] + (4, 1))
		oxr = other.x.reshape(other.x.shape[:-1] + (1, 4))

		prod = sxr * oxr
		return_shape = prod.shape[:-1]
		prod = prod.reshape((-1, 4, 4)).transpose((1, 2, 0))

		ret = np.array([(prod[0, 0] - prod[1, 1]
						 - prod[2, 2] - prod[3, 3]),
						(prod[0, 1] + prod[1, 0]
						 + prod[2, 3] - prod[3, 2]),
						(prod[0, 2] - prod[1, 3]
						 + prod[2, 0] + prod[3, 1]),
						(prod[0, 3] + prod[1, 2]
						 - prod[2, 1] + prod[3, 0])],
					   dtype=float,
					   order='F').T
		return self.__class__(ret.reshape(return_shape))

	def as_v_theta(self):
		"""Return the v, theta equivalent of the (normalized) quaternion"""
		x = self.x.reshape((-1, 4)).T

		# compute theta
		norm = np.sqrt((x ** 2).sum(0))
		theta = 2 * np.arccos(x[0] / norm)

		# compute the unit vector
		v = np.array(x[1:], order='F', copy=True)
		v /= np.sqrt(np.sum(v ** 2, 0))

		# reshape the results
		v = v.T.reshape(self.x.shape[:-1] + (3,))
		theta = theta.reshape(self.x.shape[:-1])

		return v, theta

	def as_rotation_matrix(self):
		"""Return the rotation matrix of the (normalized) quaternion"""
		v, theta = self.as_v_theta()

		shape = theta.shape
		theta = theta.reshape(-1)
		v = v.reshape(-1, 3).T
		c = np.cos(theta)
		s = np.sin(theta)

		mat = np.array([[v[0] * v[0] * (1. - c) + c,
						 v[0] * v[1] * (1. - c) - v[2] * s,
						 v[0] * v[2] * (1. - c) + v[1] * s],
						[v[1] * v[0] * (1. - c) + v[2] * s,
						 v[1] * v[1] * (1. - c) + c,
						 v[1] * v[2] * (1. - c) - v[0] * s],
						[v[2] * v[0] * (1. - c) - v[1] * s,
						 v[2] * v[1] * (1. - c) + v[0] * s,
						 v[2] * v[2] * (1. - c) + c]],
					   order='F').T
		return mat.reshape(shape + (3, 3))

	def rotate(self, points):
		M = self.as_rotation_matrix()
		return np.dot(points, M.T)


def project_points(points, q, view, vertical=[0, 1, 0]):
	"""Project points using a quaternion q and a view v

	Parameters
	----------
	points : array_like
		array of last-dimension 3
	q : Quaternion
		quaternion representation of the rotation
	view : array_like
		length-3 vector giving the point of view
	vertical : array_like
		direction of y-axis for view.  An error will be raised if it
		is parallel to the view.

	Returns
	-------
	proj: array_like
		array of projected points: same shape as points.
	"""
	points = np.asarray(points)
	view = np.asarray(view)

	xdir = np.cross(vertical, view).astype(float)

	if np.all(xdir == 0):
		raise ValueError("vertical is parallel to v")

	xdir /= np.sqrt(np.dot(xdir, xdir))

	# get the unit vector corresponing to vertical
	ydir = np.cross(view, xdir)
	ydir /= np.sqrt(np.dot(ydir, ydir))

	# normalize the viewer location: this is the z-axis
	v2 = np.dot(view, view)
	zdir = view / np.sqrt(v2)

	# rotate the points
	R = q.as_rotation_matrix()
	Rpts = np.dot(points, R.T)

	# project the points onto the view
	dpoint = Rpts - view
	dpoint_view = np.dot(dpoint, view).reshape(dpoint.shape[:-1] + (1,))
	dproj = -dpoint * v2 / dpoint_view

	trans =  list(range(1, dproj.ndim)) + [0]
	return np.array([np.dot(dproj, xdir),
					 np.dot(dproj, ydir),
					 -np.dot(dpoint, zdir)]).transpose(trans)


class PolyView3D(plt.Axes):
	def __init__(self, view=(0, 0, 10), fig=None,
				 rect=[0, 0, 1, 1], **kwargs):
		if fig is None:
			fig = plt.gcf()

		self.view = np.asarray(view)
		self.start_rot = Quaternion.from_v_theta((1, -1, 0), -np.pi / 6)

		# Define movement for up/down arrows or up/down mouse movement
		self._ax_UD = (1, 0, 0)
		self._step_UD = 0.01

		# Define movement for left/right arrows or left/right mouse movement
		self._ax_LR = (0, -1, 0)
		self._step_LR = 0.01

		# Internal state variable
		self._button1 = False
		self._button2 = False
		self._event_xy = None
		self._current_rot = self.start_rot
		self._npts = [1]
		self._xyzs = [[0, 0, 0]]
		self._xys = [[0, 0]]
		self._polys = []

		# initialize the axes.  We'll set some keywords by default
		kwargs.update(dict(aspect='equal',
						   xlim=(-2.5, 2.5), ylim=(-2.5, 2.5),
						   frameon=False, xticks=[], yticks=[]))
		super(PolyView3D, self).__init__(fig, rect, **kwargs)
		self.xaxis.set_major_formatter(plt.NullFormatter())
		self.yaxis.set_major_formatter(plt.NullFormatter())

		# connect some GUI events
		self.figure.canvas.mpl_connect('button_press_event',
									   self._mouse_press)
		self.figure.canvas.mpl_connect('button_release_event',
									   self._mouse_release)
		self.figure.canvas.mpl_connect('motion_notify_event',
									   self._mouse_motion)
		self.figure.canvas.mpl_connect('key_press_event',
									   self._key_press)
		self.figure.canvas.mpl_connect('key_release_event',
									   self._key_release)

	def poly3D(self, xyz, **kwargs):
		"""Add a 3D polygon to the axes

		Parameters
		----------
		xyz : array_like
			an array of vertices, shape is (Npts, 3)
		**kwargs :
			additional arguments are passed to plt.Polygon
		"""
		xyz = np.asarray(xyz)
		self._npts.append(self._npts[-1] + xyz.shape[0])
		self._xyzs = np.vstack([self._xyzs, xyz])

		self._polys.append(plt.Polygon(xyz[:, :2], **kwargs))
		self.add_patch(self._polys[-1])
		self._update_projection()

	def poly3D_batch(self, xyzs, **kwargs):
		"""Add multiple 3D polygons to the axes.

		This is equivalent to

			for i in range(len(xyzs)):
				kwargs_i = dict([(key, kwargs[key][i]) for key in keys])
				ax.poly3D(xyzs[i], **kwargs_i)

		But it is much more efficient (it avoids redrawing each time).

		Parameters
		xyzs : list
			each item of xyzs is an array of shape (Npts, 3) where Npts may
			be different for each item
		**kwargs :
			additional arguments should be lists of the same length as xyzs,
			and each item will be passed to the ``plt.Polygon`` constructor.
		"""
		N = len(xyzs)
		kwds = [dict([(key, kwargs[key][i]) for key in kwargs])
				for i in range(N)]
		polys = [plt.Polygon(xyz[:, :2], **kwd)
				 for (xyz, kwd) in zip(xyzs, kwds)]
		npts = self._npts[-1] + np.cumsum([len(xyz) for xyz in xyzs])
		self._polys += polys
		self._npts += list(npts)
		self._xyzs = np.vstack([self._xyzs] + xyzs)
		self._xys = np.array(self._xyzs[:, :2], dtype=float)

		[self.add_patch(p) for p in polys]
		self._update_projection()

	def rotate(self, rot):
		self._current_rot = self._current_rot * rot

	def _update_projection(self):
		proj = project_points(self._xyzs, self._current_rot, self.view)
		for i in range(len(self._polys)):
			p = proj[self._npts[i]:self._npts[i + 1]]
			self._polys[i].set_xy(p[:, :2])
			self._polys[i].set_zorder(-p[:-1, 2].mean())
		self.figure.canvas.draw()

	def _key_press(self, event):
		"""Handler for key press events"""
		if event.key == 'shift':
			self._ax_LR = (0, 0, 1)

		elif event.key == 'right':
			self.rotate(Quaternion.from_v_theta(self._ax_LR,
												5 * self._step_LR))
		elif event.key == 'left':
			self.rotate(Quaternion.from_v_theta(self._ax_LR,
												-5 * self._step_LR))
		elif event.key == 'up':
			self.rotate(Quaternion.from_v_theta(self._ax_UD,
												5 * self._step_UD))
		elif event.key == 'down':
			self.rotate(Quaternion.from_v_theta(self._ax_UD,
												-5 * self._step_UD))
		self._update_projection()

	def _key_release(self, event):
		"""Handler for key release event"""
		if event.key == 'shift':
			self._ax_LR = (0, -1, 0)

	def _mouse_press(self, event):
		"""Handler for mouse button press"""
		self._event_xy = (event.x, event.y)
		if event.button == 1:
			self._button1 = True
		elif event.button == 3:
			self._button2 = True

	def _mouse_release(self, event):
		"""Handler for mouse button release"""
		self._event_xy = None
		if event.button == 1:
			self._button1 = False
		elif event.button == 3:
			self._button2 = False

	def _mouse_motion(self, event):
		"""Handler for mouse motion"""
		if self._button1 or self._button2:
			dx = event.x - self._event_xy[0]
			dy = event.y - self._event_xy[1]
			self._event_xy = (event.x, event.y)

			if self._button1:
				rot1 = Quaternion.from_v_theta(self._ax_UD,
											   self._step_UD * dy)
				rot2 = Quaternion.from_v_theta(self._ax_LR,
											   self._step_LR * dx)
				self.rotate(rot1 * rot2)

				self._update_projection()

			if self._button2:
				factor = 1 - 0.003 * (dx + dy)
				xlim = self.get_xlim()
				ylim = self.get_ylim()
				self.set_xlim(factor * xlim[0], factor * xlim[1])
				self.set_ylim(factor * ylim[0], factor * ylim[1])

				self.figure.canvas.draw()


def cube_axes(N=1, **kwargs):
	"""Create an N x N x N rubiks cube

	kwargs are passed to the PolyView3D instance.
	"""
	stickerwidth = 0.9
	small = 0.5 * (1. - stickerwidth)
	d1 = 1 - small
	d2 = 1 - 2 * small
	d3 = 1.01
	base_sticker = np.array([[d1, d2, d3], [d2, d1, d3],
							 [-d2, d1, d3], [-d1, d2, d3],
							 [-d1, -d2, d3], [-d2, -d1, d3],
							 [d2, -d1, d3], [d1, -d2, d3],
							 [d1, d2, d3]], dtype=float)

	base_face = np.array([[1, 1, 1],
						  [1, -1, 1],
						  [-1, -1, 1],
						  [-1, 1, 1],
						  [1, 1, 1]], dtype=float)

	x, y, z = np.eye(3)
	rots = [Quaternion.from_v_theta(x, theta)
			for theta in (np.pi / 2, -np.pi / 2)]
	rots += [Quaternion.from_v_theta(y, theta)
			 for theta in (np.pi / 2, -np.pi / 2, np.pi, 2 * np.pi)]

	cubie_width = 2. / N
	translations = np.array([[-1 + (i + 0.5) * cubie_width,
							  -1 + (j + 0.5) * cubie_width, 0]
							 for i in range(N) for j in range(N)])

	colors = ['blue', 'green', 'white', 'yellow', 'orange', 'red']

	factor = np.array([1. / N, 1. / N, 1])

	ax = PolyView3D(**kwargs)
	facecolor = []
	polys = []

	for t in translations:
		base_face_trans = factor * base_face + t
		base_sticker_trans = factor * base_sticker + t
		for r, c in zip(rots, colors):
			polys += [r.rotate(base_face_trans),
					  r.rotate(base_sticker_trans)]
			facecolor += ['k', c]

	ax.poly3D_batch(polys, facecolor=facecolor)

	ax.figure.text(0.05, 0.05,
				   ("Drag Mouse or use arrow keys to change perspective.\n"
					"Hold shift to adjust z-axis rotation"),
				   ha='left', va='bottom')
	return ax



class Cube:
	"""Magic Cube Representation"""
	# define some attribues
	default_plastic_color = 'black'
	default_face_colors = ["w", "#ffcf00",
						   "#00008f", "#009f0f",
						   "#ff6f00", "#cf0000",
						   "gray", "none"]
	base_face = np.array([[1, 1, 1],
						  [1, -1, 1],
						  [-1, -1, 1],
						  [-1, 1, 1],
						  [1, 1, 1]], dtype=float)
	stickerwidth = 0.9
	stickermargin = 0.5 * (1. - stickerwidth)
	stickerthickness = 0.001
	(d1, d2, d3) = (1 - stickermargin,
					1 - 2 * stickermargin,
					1 + stickerthickness)
	base_sticker = np.array([[d1, d2, d3], [d2, d1, d3],
							 [-d2, d1, d3], [-d1, d2, d3],
							 [-d1, -d2, d3], [-d2, -d1, d3],
							 [d2, -d1, d3], [d1, -d2, d3],
							 [d1, d2, d3]], dtype=float)

	base_face_centroid = np.array([[0, 0, 1]])
	base_sticker_centroid = np.array([[0, 0, 1 + stickerthickness]])

	# Define rotation angles and axes for the six sides of the cube
	x, y, z = np.eye(3)
	rots = [Quaternion.from_v_theta(np.eye(3)[0], theta)
	for theta in (np.pi / 2, -np.pi / 2)]
	rots += [Quaternion.from_v_theta(np.eye(3)[1], theta)
	for theta in (np.pi / 2, -np.pi / 2, np.pi, 2 * np.pi)]

	# define face movements
	facesdict = dict(F=z, B=-z,
					 R=x, L=-x,
					 U=y, D=-y)

	def __init__(self, N=3, plastic_color=None, face_colors=None):
		self.N = N
		if plastic_color is None:
			self.plastic_color = self.default_plastic_color
		else:
			self.plastic_color = plastic_color

		if face_colors is None:
			self.face_colors = self.default_face_colors
		else:
			self.face_colors = face_colors

		self._move_list = []
		self._initialize_arrays()

	def _initialize_arrays(self):
		# initialize centroids, faces, and stickers.  We start with a
		# base for each one, and then translate & rotate them into position.

		# Define N^2 translations for each face of the cube
		cubie_width = 2. / self.N
		translations = np.array([[[-1 + (i + 0.5) * cubie_width,
								   -1 + (j + 0.5) * cubie_width, 0]]
								 for i in range(self.N)
								 for j in range(self.N)])

		# Create arrays for centroids, faces, stickers, and colors
		face_centroids = []
		faces = []
		sticker_centroids = []
		stickers = []
		colors = []

		factor = np.array([1. / self.N, 1. / self.N, 1])

		for i in range(6):
			M = self.rots[i].as_rotation_matrix()
			faces_t = np.dot(factor * self.base_face
							 + translations, M.T)
			stickers_t = np.dot(factor * self.base_sticker
								+ translations, M.T)
			face_centroids_t = np.dot(self.base_face_centroid
									  + translations, M.T)
			sticker_centroids_t = np.dot(self.base_sticker_centroid
										 + translations, M.T)
			colors_i = i + np.zeros(face_centroids_t.shape[0], dtype=int)

			# append face ID to the face centroids for lex-sorting
			face_centroids_t = np.hstack([face_centroids_t.reshape(-1, 3),
										  colors_i[:, None]])
			sticker_centroids_t = sticker_centroids_t.reshape((-1, 3))

			faces.append(faces_t)
			face_centroids.append(face_centroids_t)
			stickers.append(stickers_t)
			sticker_centroids.append(sticker_centroids_t)
			colors.append(colors_i)

		self._face_centroids = np.vstack(face_centroids)
		self._faces = np.vstack(faces)
		self._sticker_centroids = np.vstack(sticker_centroids)
		self._stickers = np.vstack(stickers)
		self._colors = np.concatenate(colors)

		self._sort_faces()

	def _sort_faces(self):
		# use lexsort on the centroids to put faces in a standard order.
		ind = np.lexsort(self._face_centroids.T)
		self._face_centroids = self._face_centroids[ind]
		self._sticker_centroids = self._sticker_centroids[ind]
		self._stickers = self._stickers[ind]
		self._colors = self._colors[ind]
		self._faces = self._faces[ind]

	def rotate_face(self, f, n=1, layer=0):
		"""Rotate Face"""
		if layer < 0 or layer >= self.N:
			raise ValueError('layer should be between 0 and N-1')

		try:
			f_last, n_last, layer_last = self._move_list[-1]
		except:
			f_last, n_last, layer_last = None, None, None

		if (f == f_last) and (layer == layer_last):
			ntot = (n_last + n) % 4
			if abs(ntot - 4) < abs(ntot):
				ntot = ntot - 4
			if np.allclose(ntot, 0):
				self._move_list = self._move_list[:-1]
			else:
				self._move_list[-1] = (f, ntot, layer)
		else:
			self._move_list.append((f, n, layer))
		
		v = self.facesdict[f]
		r = Quaternion.from_v_theta(v, n * np.pi / 2)
		M = r.as_rotation_matrix()

		proj = np.dot(self._face_centroids[:, :3], v)
		cubie_width = 2. / self.N
		flag = ((proj > 0.9 - (layer + 1) * cubie_width) &
				(proj < 1.1 - layer * cubie_width))

		for x in [self._stickers, self._sticker_centroids,
				  self._faces]:
			x[flag] = np.dot(x[flag], M.T)
		self._face_centroids[flag, :3] = np.dot(self._face_centroids[flag, :3],
												M.T)

	def draw_interactive(self, first_shuffle = None, resolution_shuffle = None):
		fig = plt.figure(figsize=(5, 5))
		fig.add_axes(InteractiveCube(self, first_shuffle, resolution_shuffle, self.N))
		return fig


class InteractiveCube(plt.Axes):
	def __init__(self, cube=None, first_shuffle = None, resolution_shuffle = None, N=3,
				 interactive=True,
				 view=(0, 0, 10),
				 fig=None, rect=[0, 0.16, 1, 0.84],
				 **kwargs):
		if cube is None:
			self.cube = Cube(3)
		elif isinstance(cube, Cube):
			self.cube = cube
		else:
			self.cube = Cube(cube)
		
		self.first_shuffle = first_shuffle
		self.resolution_shuffle = resolution_shuffle
		self.solved = True
		self.N = N
		self._view = view
		self._start_rot = Quaternion.from_v_theta((1, -1, 0),
												  -np.pi / 6)

		if fig is None:
			fig = plt.gcf()

		# disable default key press events
		callbacks = fig.canvas.callbacks.callbacks
		del callbacks['key_press_event']

		# add some defaults, and draw axes
		kwargs.update(dict(aspect=kwargs.get('aspect', 'equal'),
						   xlim=kwargs.get('xlim', (-2.0, 2.0)),
						   ylim=kwargs.get('ylim', (-2.0, 2.0)),
						   frameon=kwargs.get('frameon', False),
						   xticks=kwargs.get('xticks', []),
						   yticks=kwargs.get('yticks', [])))
		super(InteractiveCube, self).__init__(fig, rect, **kwargs)
		self.xaxis.set_major_formatter(plt.NullFormatter())
		self.yaxis.set_major_formatter(plt.NullFormatter())

		self._start_xlim = kwargs['xlim']
		self._start_ylim = kwargs['ylim']

		# Define movement for up/down arrows or up/down mouse movement
		self._ax_UD = (1, 0, 0)
		self._step_UD = 0.01

		# Define movement for left/right arrows or left/right mouse movement
		self._ax_LR = (0, -1, 0)
		self._step_LR = 0.01

		self._ax_LR_alt = (0, 0, 1)

		# Internal state variable
		self._active = False  # true when mouse is over axes
		self._button1 = False  # true when button 1 is pressed
		self._button2 = False  # true when button 2 is pressed
		self._event_xy = None  # store xy position of mouse event
		self._shift = False  # shift key pressed
		self._digit_flags = np.zeros(10, dtype=bool)  # digits 0-9 pressed

		self._current_rot = self._start_rot  #current rotation state
		self._face_polys = None
		self._sticker_polys = None

		self._draw_cube()

		# connect some GUI events
		self.figure.canvas.mpl_connect('button_press_event',
									   self._mouse_press)
		self.figure.canvas.mpl_connect('button_release_event',
									   self._mouse_release)
		self.figure.canvas.mpl_connect('motion_notify_event',
									   self._mouse_motion)
		self.figure.canvas.mpl_connect('key_release_event',
									   self._key_release)

		self._initialize_widgets()

		# write some instructions
		self.figure.text(0.05, 0.05,
						 "Mouse/arrow keys adjust view\n"
						 "U/D/L/R/B/F keys turn faces\n"
						 "(hold shift for counter-clockwise)",
						 size=10)

	def _initialize_widgets(self):
		self._ax_reset = self.figure.add_axes([0.75, 0.05, 0.2, 0.075])
		self._btn_reset = widgets.Button(self._ax_reset, 'Solve cube')
		self._btn_reset.on_clicked(self._solve_cube)

		self._ax_solve = self.figure.add_axes([0.55, 0.05, 0.2, 0.075])
		self._btn_solve = widgets.Button(self._ax_solve, 'Input shuffle')
		self._btn_solve.on_clicked(self._starting_cube)
  

	def _project(self, pts):
		return project_points(pts, self._current_rot, self._view, [0, 1, 0])

	def _draw_cube(self):
		stickers = self._project(self.cube._stickers)[:, :, :2]
		faces = self._project(self.cube._faces)[:, :, :2]
		face_centroids = self._project(self.cube._face_centroids[:, :3])
		sticker_centroids = self._project(self.cube._sticker_centroids[:, :3])

		plastic_color = self.cube.plastic_color
		colors = np.asarray(self.cube.face_colors)[self.cube._colors]
		face_zorders = -face_centroids[:, 2]
		sticker_zorders = -sticker_centroids[:, 2]

		if self._face_polys is None:
			# initial call: create polygon objects and add to axes
			self._face_polys = []
			self._sticker_polys = []

			for i in range(len(colors)):
				fp = plt.Polygon(faces[i], facecolor=plastic_color,
								 zorder=face_zorders[i])
				sp = plt.Polygon(stickers[i], facecolor=colors[i],
								 zorder=sticker_zorders[i])

				self._face_polys.append(fp)
				self._sticker_polys.append(sp)
				self.add_patch(fp)
				self.add_patch(sp)
		else:
			# subsequent call: update the polygon objects
			for i in range(len(colors)):
				self._face_polys[i].set_xy(faces[i])
				self._face_polys[i].set_zorder(face_zorders[i])
				self._face_polys[i].set_facecolor(plastic_color)

				self._sticker_polys[i].set_xy(stickers[i])
				self._sticker_polys[i].set_zorder(sticker_zorders[i])
				self._sticker_polys[i].set_facecolor(colors[i])

		self.figure.canvas.draw()

	def rotate(self, rot):
		self._current_rot = self._current_rot * rot

	def rotate_face(self, face, turns=1, layer=0, steps=5):
		if not np.allclose(turns, 0):
			for i in range(steps):
				self.cube.rotate_face(face, turns * 1. / steps,
									  layer=layer)
				self._draw_cube()

	def _solve_cube(self, *args): # originally _reset_view
		if (self.solved == False):
			for move in self.resolution_shuffle:
				print(f"applying move {move}")
				self._do_moves(move)
			self.solved = True

	def _starting_cube(self, *args): # originally _reset_cube
		for move in self.first_shuffle:
			print(f"applying move {move}")
			self._do_moves(move)
		self.solved = False
	

	def _do_moves(self, move):
		if move.endswith("'"):
			direction = -1
		elif move.endswith("2"):
			direction = 2
		else:
			direction = 1
		move = move[0]
		self.rotate_face(move, direction)
		plt.pause(0.01)


	def _key_press(self, event):
		"""Handler for key press events"""
		if event.key == 'shift':
			self._shift = True
		elif event.key.isdigit():
			self._digit_flags[int(event.key)] = 1
		elif event.key == 'right':
			if self._shift:
				ax_LR = self._ax_LR_alt
			else:
				ax_LR = self._ax_LR
			self.rotate(Quaternion.from_v_theta(ax_LR,
												5 * self._step_LR))
		elif event.key == 'left':
			if self._shift:
				ax_LR = self._ax_LR_alt
			else:
				ax_LR = self._ax_LR
			self.rotate(Quaternion.from_v_theta(ax_LR,
												-5 * self._step_LR))
		elif event.key == 'up':
			self.rotate(Quaternion.from_v_theta(self._ax_UD,
												5 * self._step_UD))
		elif event.key == 'down':
			self.rotate(Quaternion.from_v_theta(self._ax_UD,
												-5 * self._step_UD))
		self._draw_cube()

	def _key_release(self, event):
		"""Handler for key release event"""
		if event.key == 'shift':
			self._shift = False
		elif event.key.isdigit():
			self._digit_flags[int(event.key)] = 0

	def _mouse_press(self, event):
		"""Handler for mouse button press"""
		self._event_xy = (event.x, event.y)
		if event.button == 1:
			self._button1 = True
		elif event.button == 3:
			self._button2 = True

	def _mouse_release(self, event):
		"""Handler for mouse button release"""
		self._event_xy = None
		if event.button == 1:
			self._button1 = False
		elif event.button == 3:
			self._button2 = False

	def _mouse_motion(self, event):
		"""Handler for mouse motion"""
		if self._button1 or self._button2:
			dx = event.x - self._event_xy[0]
			dy = event.y - self._event_xy[1]
			self._event_xy = (event.x, event.y)

			if self._button1:
				if self._shift:
					ax_LR = self._ax_LR_alt
				else:
					ax_LR = self._ax_LR
				rot1 = Quaternion.from_v_theta(self._ax_UD,
											   self._step_UD * dy)
				rot2 = Quaternion.from_v_theta(ax_LR,
											   self._step_LR * dx)
				self.rotate(rot1 * rot2)

				self._draw_cube()

			if self._button2:
				factor = 1 - 0.003 * (dx + dy)
				xlim = self.get_xlim()
				ylim = self.get_ylim()
				self.set_xlim(factor * xlim[0], factor * xlim[1])
				self.set_ylim(factor * ylim[0], factor * ylim[1])

				self.figure.canvas.draw()


def parse_args(argv):
	first_shuffle = argv[1].split()
	resolution_shuffle = argv[2].split()
	return (first_shuffle, resolution_shuffle)

if __name__ == "__main__":

	if len(sys.argv) != 3:
		print("ERROR in parsing for visual")
		sys.exit()

	first_shuffle, resolution_shuffle = parse_args(sys.argv)

	print(f"\nIN VISU:\n{first_shuffle = }\n{resolution_shuffle = }")

	c = Cube(3)
	c.draw_interactive(first_shuffle, resolution_shuffle)
	plt.show()
