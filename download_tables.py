import boto3
import os
from os import path

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
	for s3_object in my_bucket.objects.all():
		print(f"Dowloading {s3_object.key} of size \t{s3_object.size}")
		filename = path.join(os.environ["WORKDIR"], s3_object.key)
		my_bucket.download_file(s3_object.key, filename)

if __name__ == "__main__":
	download_tables()