#Python 2.7.13
#QR Decomp
#Original Author: SafetyLok


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


def qr_decomp(matX, matY, poly_degree, bPrint):
	#length of the drag (x) and veloc (y)
	#d_len = len(dict_heights_d[iHeight])
	#v_len = len(dict_heights_v[iHeight])
	#print d_arr

	#gimme some test data
	#this will make testing a bit easier
	#v_arr = [0.537582397460938, 3.93385291099548, 7.75982713699341, 11.9504404067993, 15.5886201858521, 20.0807590484619, 24.9874591827393, 30.4827308654785, 36.2020111083984, 40.598461151123, 42.8510284423828, 46.5690803527832, 51.9541282653809, 55.2913093566895, 59.9744300842285, 65.2611465454102, 68.8996276855469]
	#d_arr = [543, 529, 537, 517, 521, 514, 509, 500, 490, 476, 454, 456, 413, 430, 405, 393, 350]
	y_len = len(matY)
	x_len = len(matX)
	

	
	iVMSize = y_len
	iVNSize = poly_degree + 1
	iMatrixN = poly_degree + 1
	if bPrint == True:
		print 'poly degree = ', poly_degree 
	
	#create a vandermonde matrix
	matVan = np.zeros((iVMSize + 1, iMatrixN))

	#fill our matrix with all ones
	#if we have a 3x3 matrix the our output is:
	#V =
	#     0     0     1
	#     0     0     1
	#     0     0     1
	for iX in range(0, iVMSize):
		#'rows,cols
		matVan[iX, iMatrixN - 1] = 1.0
	if bPrint == True:
		print 'Vandermode Matrix:'
		pprint.pprint(matVan)

	
	#I'd really like to implement this in matlab
	#Array multiplication. A.*B is the element-by-element product of the arrays A and B. A and B must have the same size, unless one of them is a scalar. 
	#where 2 = poly requested value
	#for j = 2:-1:1
	#	V(:,j) = x.*V(:,j+1)
	#End
	
	#'here our array looks like:
	#'V =
	#'     0     0     1
	#'     0     0     1
	#'     0     0     1
	#'assume we have X= 10, 25, 30
	#'we need to have on the first pass
	#'V =
	#'     0    10     1
	#'     0    25     1
	#'     0    30     1
	
	#needs to be to -1, not zero due to the way this thing counts.
	for iColCounter in range(iMatrixN - 2, -1, -1):
		for iRowCounter in range(0, iVMSize):
			matVan[iRowCounter, iColCounter] = matX[iRowCounter] * matVan[iRowCounter, iColCounter + 1]
	if bPrint == True:
		print 'Vandermonde Matrix (Mult):'
		pprint.pprint(matVan)
		
	#now try and solve for least squares
	
	#create a matrix with zero's
	lsV = np.zeros((iVMSize, iMatrixN))
	
	#could also try a direct load
	#but the data type would not be understood, makes it hard, need to do a manal copy.
	#matV = np.matrix(matY, matX)
	
	#load up our matrix
	for iX in range(0, iVMSize):
		for iY in range(0, iMatrixN):
			#'rows,cols
			lsV[iX, iY] = matVan[iX, iY]
	#pprint.pprint(lsV)
	
	#do the QR
	lsQR_q, lsQR_r = np.linalg.qr(lsV)
	#pprint.pprint(lsQR)
	
	#get the size
	iQm, iQn = lsQR_q.shape


	#Copy to a new Q
	m_Q = np.zeros((iQm, iQn))
	
	#Copy Across
	for iX in range (0, iQm):
		for iY in range(0, iQn):
			#rows,cols
			m_Q[iX, iY] = lsQR_q[iX, iY]
	if bPrint == True:
		print 'Q Matrix: ', iQm, " x ", iQn 
		pprint.pprint(m_Q)

	
	#get the size
	iRm, iRn = lsQR_r.shape

	m_R = np.zeros((iRm, iRn))

	#copy
	for iX in range (0, iRm):
		for iY in range (0, iRn):
			#'rows,cols
			m_R[iX, iY] = lsQR_r[iX, iY]

	if bPrint == True:
		print 'R Matrix: ', iRm, "x", iRn 
		pprint.pprint(m_R)
			
	#create our Q'
	m_Qdash = lsQR_q.transpose()

	#get its size
	iQdashm, iQdashn = m_Qdash.shape

	m_Qdm_R = np.zeros((iQdashm, iQdashn))

	#size is 3x17
	for iX in range (0, iQdashm):
		for iY in range (0, iQdashn):
			#'rows,cols
			m_Qdm_R[iX, iY] = m_Qdash[iX, iY]
			
	if bPrint == True:
		print 'Qdash Matrix: ', m_Qdm_R.shape
		pprint.pprint(m_Qdm_R)

	#compute our P matrix
	#p = R \ (Q' * y);

	#create our Y matrix
	#size is 17x1
	bbY = np.zeros((x_len, 1))
	for iCounter in range (0, x_len):
		bbY[iCounter, 0] = matY[iCounter]
		
	if bPrint == True:
		print 'Y Matrix: ', bbY.shape
		pprint.pprint(bbY)
	
	#do the multiplication of Q' x Y
	#Q' is 3 x 17
	#Y  is 17 x 1
	#the result should be [3x1]
	
	#bbQdashxY = m_Qdm_R * bbY
	#bbQdashxY = np.inner(m_Qdm_R, bbY)
	#damn..
	bbQdashxY = np.dot(m_Qdm_R, bbY)
	if bPrint == True:
		print 'QdashByY Matrix: ', bbQdashxY.shape
		pprint.pprint(bbQdashxY)
	
	#finally divide
	#matrixP = np.divide(lsQR_r, bbQdashxY)
	matrixP = np.linalg.lstsq(lsQR_r, bbQdashxY)[0]
	
	if bPrint == True:
		print 'P Matrix: ' #, matrixP.shape
		pprint.pprint(matrixP) 
	
	return matrixP