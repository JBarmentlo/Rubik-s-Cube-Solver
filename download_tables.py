import boto3
import os
from os import path
from tqdm import tqdm

# ! Make environment vairables 
# ! export ID='asdasdasdXsdfFXsdf'
# ! export KEY='Jsdfasdasdasdasd'
# ! export WORKDIR=$(pwd)

def download_tables():
	# client = boto3.client(
	# 	service_name = 's3',
	# 	aws_access_key_id = os.environ["ID"],
	# 	aws_secret_access_key = os.environ["KEY"],
	# )
	resource = boto3.resource(
		service_name = 's3',
		aws_access_key_id = os.environ["ID"],
		aws_secret_access_key = os.environ["KEY"],
	)
	my_bucket = resource.Bucket('roobik-tables')


	total_size = 0
	for s3_object in my_bucket.objects.all():
		total_size += s3_object.size

	for s3_object in my_bucket.objects.all():
		if (s3_object.size > 1.1e9):
			print(f"Dowloading {s3_object.key:<50} of size:  {(s3_object.size / 1000000000):6.2f} Gb")
		elif (s3_object.size > 1.1e6):
			print(f"Dowloading {s3_object.key:<50} of size:  {(s3_object.size / 1000000):6.2f} Mb")
		else:
			print(f"Dowloading {s3_object.key:<50} of size:  {(s3_object.size / 1000):6.2f} Kb")

		filename = path.join(os.environ["WORKDIR"], s3_object.key)
		with tqdm(total=s3_object.size) as pbar:
			my_bucket.download_file(s3_object.key, filename, Callback=lambda bytes_transferred: pbar.update(bytes_transferred))
		print("\n")

if __name__ == "__main__":
	download_tables()