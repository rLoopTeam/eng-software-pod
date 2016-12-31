#Python 2.7.13
#Processing script to convert a43 brake data table to a suitable format for RM48
#Original Author: SafetyLok
#example: d:\python27\python.exe go.py ../a34data.csv -p3 -y3 -v25 -g0

#Need various toolboxes
import argparse

#python -m pip install -U pip setuptools
#python -m pip install matplotlib
import matplotlib.pyplot as plt

#python -m pip install pandas
#data analysis lib
import pandas as pd
import numpy as np

#needed for CSV IO
import csv
import pprint
from qr import qr_decomp

#get command line for the a34data.csv
m_parse = argparse.ArgumentParser()
m_parse.add_argument('csv_file')
m_parse.add_argument('-p', '--polyorder', help="Polynomial Degree", type=int, default=2, required=True)
m_parse.add_argument('-y', '--vertpoly', help="Vertical Polynomial Degree", type=int, default=2, required=True)
m_parse.add_argument('-v', '--min_veloc', help="Minimum Velocity To Use", type=int, default=30, required=True)
m_parse.add_argument('-g', '--produce_graphs', help="Produce Graphs = 1", type=int, default=0, required=False)
m_args = m_parse.parse_args()

#read the CSV file in (assume that we are inputting correctly)
#short by height
m_csv = pd.read_csv(m_args.csv_file)
m_csv_sort = m_csv.sort(['h'])

#create an array of unique heights on the sorted array
m_unique_heights = m_csv_sort['h'].unique()
print m_unique_heights


#create the dictionary of all the i-beam distances (heights) in the file
#drag and veloc are separated here
dict_heights_d = {}
dict_heights_v = {}

#go through each height
for iHeight in m_unique_heights:
	

	#see if our current height key is in the dict
	if not iHeight in dict_heights_d:
	
		#create the new dictionary entry
		dict_heights_d[iHeight] = []
		dict_heights_v[iHeight] = []
		
	#go through each row in the CSV
	for index, row in m_csv.iterrows():
		
		#if the height col in the current row is the same as the height loop
		#then add the new 
		if row['h'] == iHeight:
		
			#we want F_drag, v
			dict_heights_d[iHeight].append(row['F_drag'])
			#np.append(dict_heights_d[iHeight], row['F_drag'])
			dict_heights_v[iHeight].append(row['v'])

#do a quick print of the heights dictionary so as we can confirm
#pprint.pprint(dict_heights_d)
#pprint.pprint(dict_heights_v)

#save off all the CSV files into the currnet dir, this allows us to call them up again.

#we need to limit our veloc to some value as it will be imposs to curve
#fit to the 0 to 30m/s mark on this data table.
veloc_limit = m_args.min_veloc
veloc_max = 160

#the poly degree, probably should make this an arg
poly_degree = m_args.polyorder

#velocity tables
veloc_tables_for_height = {}

#go through each height and compute the QR decomposition of each veloc vs drag for each height array
for iHeight in m_unique_heights:

	#get the two arrays for the current height (x,y)
	d_arrX = dict_heights_d[iHeight]
	v_arrX = dict_heights_v[iHeight]
	
	v_arr = []
	d_arr = []
	
	#manually tirm
	for iTrim in range(0, len(v_arrX)):
		if v_arrX[iTrim] > veloc_limit:
			v_arr.append(v_arrX[iTrim])
			d_arr.append(d_arrX[iTrim])
	#pprint.pprint(v_arr)
	
 	#do the QR
	matrixP = qr_decomp(v_arr, d_arr, poly_degree, False)
	
	#this is now in terms of
	#y = matrixP[0].x^2 + matrixP[1].x + matrixP[2]
	
	#test
	#x = veloc
	#y = drag
	testX = v_arr[0]
	testY = 0.0
	
	#thx ryan!
	for idx, coefficient in enumerate(matrixP):
		# length of coefficients (in this case, 6) - the list index (0 to 5) - 1
		power = len(matrixP) - idx - 1
		testY += coefficient * testX**power
	
	print 'Test: (x=', testX, ')', testY, 'expected: ', d_arr[0]
	
	#now make some graphs
	if m_args.produce_graphs == 1:
		plt.figure()
		plt.title('QR: Height ' + str(iHeight) + ', Vmin ' + str(veloc_limit) + ', Poly ' + str(poly_degree))

		#x is in terms of veloc
		#manually plot out our formula
		yy = []
		#mult size by 100 to give some nice smooth data
		#min(v_arr)
		x = np.linspace(0, max(v_arr), len(v_arr)*100)
		for xx in x:
			ay = 0.0
			for idx, coefficient in enumerate(matrixP):
				# length of coefficients (in this case, 6) - the list index (0 to 5) - 1
				power = len(matrixP) - idx - 1
				ay += coefficient * xx**power
			yy.append(ay)

		plt.ylabel('Drag Force n')
		plt.xlabel('Velocity m/s')
		#plt.text(0.02,0.86,'contour labels:\nmagnet to rail gap [m]\n- braking force\n-- normal force',fontsize=10, transform=ax1.transAxes)
		plt.grid()
		plt.plot(x, yy, label='Polynomial')
		plt.plot(v_arrX, d_arrX, label='A34 Data')
		plt.legend()
		#plt.show()
		filename = 'qr_fig_h_'
		newname = 'OUTPUT/GRAPHS/{}{:f}.png'.format(filename, iHeight)
		#plt.savefig(newname)
		plt.close()
	
	#At this point here we have an array of polys for a given height, lets
	#save these polys off into an easy to handle format so as we can re-load them and
	#compute detailed data tables at say 1m/s veloc increments.
	newname = 'OUTPUT/COEFFS/{}{:f}.csv'.format('coeffs_', iHeight)
	np.savetxt(newname, matrixP)
	
	#create a folder for the VELOC Tables
	#the VELOC tables are a table from 0 to 160m/s producing a brake force
	#for a given height.
	#note: Tables are only valid above Vmin
	veloc_tables_for_height[iHeight] = []
	
	#up to 160m/s in 1m/s incs
	x = np.linspace(0, veloc_max, veloc_max)
	x = np.linspace(0, max(v_arr), len(v_arr)*100)
	for xx in x:
		ay = 0.0
		for idx, coefficient in enumerate(matrixP):
			# length of coefficients (in this case, 6) - the list index (0 to 5) - 1
			power = len(matrixP) - idx - 1
			ay += coefficient * xx**power
		veloc_tables_for_height[iHeight].append(ay)
	
	
#at this point in the program we have a set of n data tables where n is the heights (i-beam gap)
#These tables are computed brake forces from 0 to 160m/s in 1/ms increments
#for each of these tables we want to load up our data for each 1m/s increment and do the polyfit
#on that data such that we are polyfitting effectively columns of 1m/s increments
#this will produce 160 data tables
#these tables will be valid for every velocity and for any velocity (in 1m/s inc) we can
#determine the height for a given brake force.
veloc_tables = {}
veloc_tables_matrixP = {}

#do all our 160 velocities
for iVeloc in range(0, veloc_max):

	#create the veloc table entry, which is a dictionary of arrays
	veloc_tables[iVeloc] = []
	
	#the dictionary of our resultant matrixP (the coeffs) for a given velocity
	veloc_tables_matrixP[iVeloc] = []

	#create an array of the current velocity from all the height tables
	#imagine 6 rows in a table, these rows are the 'height tables'
	for iHeight in m_unique_heights:
	
		#add the item to the dictionary under our current velocity
		#We are building a dict of:
		#velocity[0m/s][force0, force1, force2]
		#			   [vel=0, vel=1, vel=2]
		veloc_tables[iVeloc].append(veloc_tables_for_height[iHeight][iVeloc])
		
	#print 'Veloc Table for Height Array'
	#pprint.pprint(veloc_tables[iVeloc])
		
	#here our veloc_table should look like for V=0
	#[drag for H=0, Drag for H=1, etc.]

	#at this point we have an array which represents columns of data, where each column
	#is the computed drag force at the current velocity

	#get our coeffs
	#compute such at that we have have a x = drags at current veloc, y = heights
	
	veloc_tables_matrixP[iVeloc] = qr_decomp(veloc_tables[iVeloc], m_unique_heights, m_args.vertpoly, False)

	if iVeloc >= 30:
		#do some testing
		#X = Drag at point 0
		testX = 7150.0 #veloc_tables[iVeloc][0]
		testY = 0.0
		
		#thx ryan!
		for idx, coefficient in enumerate(veloc_tables_matrixP[iVeloc]):
			# length of coefficients (in this case, 6) - the list index (0 to 5) - 1
			power = len(veloc_tables_matrixP[iVeloc]) - idx - 1
			testY += coefficient * testX**power
		
		print 'Column Test: Veloc:', iVeloc, ' Drag:', testX, ', Calc I-Beam:', testY #, ', Expected IBeam: ', iHeight #m_unique_heights[iHeight]

		#quit()
	
		#plot this graph
		if m_args.produce_graphs == 1:
			plt.figure()
			plt.title('Vertical Veloc = ' + str(iVeloc) + ', Poly = ' + str(m_args.vertpoly))


			yy = []
			#generate the values up to 10K, 100 points.
			x = np.linspace(-500, 10000, 100)
			for xx in x:
				ay = 0.0
				for idx, coefficient in enumerate(veloc_tables_matrixP[iVeloc]):
					power = len(veloc_tables_matrixP[iVeloc]) - idx - 1
					ay += coefficient * xx**power
					
				#limit for graphing purposes
				if ay > 0.05:
					ay = 0.05
				if ay < 0.00:
					ay = 0.0
					
				yy.append(ay)

			plt.ylabel('I-Beam Distance')
			plt.xlabel('Drag Force n')
			
			plt.grid()
			plt.plot(veloc_tables[iVeloc], m_unique_heights, label='A34 Data', marker='o')
			plt.plot(x, yy, label='Polynomial')
			plt.legend()
			#plt.show()
			filename = 'veloc_'
			newname = 'OUTPUT/VERTICAL/{}{:f}.png'.format(filename, iVeloc)
			plt.savefig(newname)
			plt.close()
	
			#quit()
	#At this point we know that our column tables have been curve fitted and we have the polys for
	#this table in MatrixP
	#So here we have:
	#1. A Column for every velocity
	#2. For every column a matrixP which is the equation for that current veloc
	#3. The ability to compute the brake height based on a force required.
	

#from the column tables, lets spit out a C-File

#setup the C-File
c_output = "#include ../../fcu_core.h\n"

c_output += "#ifndef WIN32\n"
c_output += "const Lfloat32 f32A34_BrakeTable[] = {\n"
c_output += "#else\n"
c_output += "Lfloat32 f32A34_BrakeTable[] = {\n"
c_output += "#endif\n"



for iVeloc in range(0, veloc_max):

	#spit out each velocity equation
	floats_str = ", ".join(str(float(x)) for x in veloc_tables_matrixP[iVeloc])
	c_output += floats_str
	c_output += ",\n"

#remove the last comma
c_output = c_output[:-2]

#append the last
c_output += "};\n"
	
with open('a34_brake_table.c', 'w') as c_file:
   c_file.write(c_output)

