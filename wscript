
import json
top = '.'
out = 'build'

def options(ctx):
	ctx.load('pebble_sdk')

def configure(ctx):
	ctx.load('pebble_sdk')

	def create_people_resource(input, output):
		json_data=open(input)
		data = json.load(json_data)

		newFile = open (output, "wb")

		for person in data['persons'] :
			newFile.write(person['firstName'] + ('\0' * (15 - len(person['firstName']))))
			newFile.write(person['surname']   + ('\0' * (15 - len(person['surname']))))

		newFile.close()

	create_people_resource('people.json','resources/raw/people.bin')

def build(ctx):
	ctx.load('pebble_sdk')

	ctx.pbl_program(source=ctx.path.ant_glob('src/**/*.c'),
	                target='pebble-app.elf')

	ctx.pbl_bundle(elf='pebble-app.elf',
	               js=ctx.path.ant_glob('src/js/**/*.js'))
