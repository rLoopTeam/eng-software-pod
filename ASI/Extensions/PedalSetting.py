import sys
import time
import clr
clr.AddReference("System.Drawing")
clr.AddReference("System.Windows.Forms")
from globals import *
import System
from System import *
from System.Windows.Forms import *
from System.ComponentModel import *
from System.Drawing import *
from clr import *

    
class PedalSensorSelectForm(System.Windows.Forms.Form):
	def __init__(self):
	    self.InitializeComponent()
	
	def InitializeComponent(self):
		self._comboBox1 = System.Windows.Forms.ComboBox()
		self._textBox1 = System.Windows.Forms.TextBox()
		self._textBox2 = System.Windows.Forms.TextBox()
		self._label1 = System.Windows.Forms.Label()
		self._label2 = System.Windows.Forms.Label()
		self._label3 = System.Windows.Forms.Label()
		self._SpeedGroupBox = System.Windows.Forms.GroupBox()
		self._TorqueGroupBox = System.Windows.Forms.GroupBox()
		self._label4 = System.Windows.Forms.Label()
		self._OffsetTextBox = System.Windows.Forms.TextBox()
		self._label5 = System.Windows.Forms.Label()
		self._GainTextBox = System.Windows.Forms.TextBox()
		self._SpeedGroupBox.SuspendLayout()
		self._TorqueGroupBox.SuspendLayout()
		self.SuspendLayout()
		# 
		# comboBox1
		# 
		self._comboBox1.FormattingEnabled = True
		self._comboBox1.Items.AddRange(System.Array[System.Object](
			["Single hall speed sensor",
			"Dual hall speed sensor",
			"FAG sensor",
			"Quadrature torque sensor",
			"Quadrature speed sensor"]))
		self._comboBox1.Location = System.Drawing.Point(60, 60)
		self._comboBox1.Name = "comboBox1"
		self._comboBox1.Size = System.Drawing.Size(170, 21)
		self._comboBox1.TabIndex = 2
		self._comboBox1.Tag = ""
		self._comboBox1.SelectedIndexChanged += self._comboBox1_SelectedIndexChanged
		# 
		# textBox1
		# 
		self._textBox1.Location = System.Drawing.Point(156, 17)
		self._textBox1.Name = "textBox1"
		self._textBox1.Size = System.Drawing.Size(55, 20)
		self._textBox1.TabIndex = 3
		self._textBox1.TextChanged += self._textBox1_TextChanged
		# 
		# textBox2
		# 
		self._textBox2.Location = System.Drawing.Point(156, 44)
		self._textBox2.Name = "textBox2"
		self._textBox2.Size = System.Drawing.Size(55, 20)
		self._textBox2.TabIndex = 5
		self._textBox2.TextChanged += self._textBox2_TextChanged
		# 
		# label1
		# 
		self._label1.Location = System.Drawing.Point(29, 37)
		self._label1.Name = "label1"
		self._label1.Size = System.Drawing.Size(138, 20)
		self._label1.TabIndex = 0
		self._label1.Text = "Pedal sensor selection"
		# 
		# label2
		# 
		self._label2.Location = System.Drawing.Point(10, 20)
		self._label2.Name = "label2"
		self._label2.Size = System.Drawing.Size(127, 20)
		self._label2.TabIndex = 1
		self._label2.Text = "Pulses per revolution"
		# 
		# label3
		# 
		self._label3.Location = System.Drawing.Point(10, 47)
		self._label3.Name = "label3"
		self._label3.Size = System.Drawing.Size(127, 20)
		self._label3.TabIndex = 2
		self._label3.Text = "Pedal delay (counts)"
		# 
		# SpeedGroupBox
		# 
		self._SpeedGroupBox.Controls.Add(self._label2)
		self._SpeedGroupBox.Controls.Add(self._label3)
		self._SpeedGroupBox.Controls.Add(self._textBox1)
		self._SpeedGroupBox.Controls.Add(self._textBox2)
		self._SpeedGroupBox.Location = System.Drawing.Point(19, 99)
		self._SpeedGroupBox.Name = "SpeedGroupBox"
		self._SpeedGroupBox.Size = System.Drawing.Size(237, 82)
		self._SpeedGroupBox.TabIndex = 6
		self._SpeedGroupBox.TabStop = False
		self._SpeedGroupBox.Text = "Speed Sensor"
		# 
		# TorqueGroupBox
		# 
		self._TorqueGroupBox.Controls.Add(self._GainTextBox)
		self._TorqueGroupBox.Controls.Add(self._label5)
		self._TorqueGroupBox.Controls.Add(self._OffsetTextBox)
		self._TorqueGroupBox.Controls.Add(self._label4)
		self._TorqueGroupBox.Location = System.Drawing.Point(19, 197)
		self._TorqueGroupBox.Name = "TorqueGroupBox"
		self._TorqueGroupBox.Size = System.Drawing.Size(236, 84)
		self._TorqueGroupBox.TabIndex = 7
		self._TorqueGroupBox.TabStop = False
		self._TorqueGroupBox.Text = "Torque Sensor"
		# 
		# label4
		# 
		self._label4.Location = System.Drawing.Point(10, 22)
		self._label4.Name = "label4"
		self._label4.Size = System.Drawing.Size(127, 18)
		self._label4.TabIndex = 0
		self._label4.Text = "Offset"
		# 
		# OffsetTextBox
		# 
		self._OffsetTextBox.Location = System.Drawing.Point(156, 19)
		self._OffsetTextBox.Name = "OffsetTextBox"
		self._OffsetTextBox.Size = System.Drawing.Size(55, 20)
		self._OffsetTextBox.TabIndex = 1
		self._OffsetTextBox.TextChanged += self._OffsetTextBox_TextChanged
		
		# 
		# label5
		# 
		self._label5.Location = System.Drawing.Point(10, 48)
		self._label5.Name = "label5"
		self._label5.Size = System.Drawing.Size(127, 23)
		self._label5.TabIndex = 2
		self._label5.Text = "Gain"
		# 
		# GainTextBox
		# 
		self._GainTextBox.Location = System.Drawing.Point(156, 45)
		self._GainTextBox.Name = "GainTextBox"
		self._GainTextBox.Size = System.Drawing.Size(55, 20)
		self._GainTextBox.TabIndex = 3
		self._GainTextBox.TextChanged += self._GainTextBox_TextChanged		
		# 
		# PedalSensorSelectForm
		# 
		self.ClientSize = System.Drawing.Size(284, 299)
		self.Controls.Add(self._TorqueGroupBox)
		self.Controls.Add(self._SpeedGroupBox)
		self.Controls.Add(self._label1)
		self.Controls.Add(self._comboBox1)
		self.Name = "PedalSensorSelectForm"
		self.Text = "Pedal Setting"
		self.Load += self.FormInitialize
		self._SpeedGroupBox.ResumeLayout(False)
		self._SpeedGroupBox.PerformLayout()
		self._TorqueGroupBox.ResumeLayout(False)
		self._TorqueGroupBox.PerformLayout()
		self.ResumeLayout(False)
		
	def FormInitialize(self, sender, e):
		if not self.DesignMode:
			self.Icon = ico;			
		array = Array[Int16](range(1))
		try:
			modbus.Read(211, 1, array)		
			self._comboBox1.SelectedIndex = array[0]
		except Exception as inst:
			print inst

		try:
			modbus.Read(234, 1, array)		
			self._textBox1.Text = str(array[0])
		except Exception as inst:
			print inst		

		try:
			modbus.Read(235, 1, array)		
			self._textBox2.Text = str(array[0])
		except Exception as inst:
			print inst		
			
		try:
			modbus.Read(182, 1, array)		
			self._OffsetTextBox.Text = "{0:.2f}".format(array[0] / 4096.0)
		except Exception as inst:
			print inst			

		try:
			modbus.Read(183, 1, array)		
			self._GainTextBox.Text = str(array[0])
		except Exception as inst:
			print inst		
		
	def _comboBox1_SelectedIndexChanged(self, sender, e):
		print self._comboBox1.SelectedIndex
		if (self._comboBox1.SelectedIndex == 3):
			self._TorqueGroupBox.Enabled = True
		else:
			self._TorqueGroupBox.Enabled = False
			
		array = Array[Int16](range(1))
		array[0] = int(self._comboBox1.SelectedIndex)
		modbus.Write(211, 1, array)

	
	def _textBox1_TextChanged(self, sender, e):
		try:
			array = Array[Int16](range(1))  	    
			array[0] = int(float(self._textBox1.Text))
			modbus.Write(234, 1, array)	  
		except ValueError as inst:
			print inst
			print self._textBox1.Text						
	
	def _textBox2_TextChanged(self, sender, e):
		try:
			array = Array[Int16](range(1)) 	    
			array[0] = int(float(self._textBox2.Text))
			modbus.Write(235, 1, array)	 
		except ValueError as inst:
			print inst
			print self._textBox2.Text		

	def _OffsetTextBox_TextChanged(self, sender, e):
		try:
			array = Array[Int16](range(1))  	    
			array[0] = int(float(self._OffsetTextBox.Text) * 4096)
			modbus.Write(182, 1, array)	  
		except ValueError as inst:
			print inst
			print self._textBox1.Text						
	
	def _GainTextBox_TextChanged(self, sender, e):
		try:
			array = Array[Int16](range(1)) 	    
			array[0] = int(float(self._GainTextBox.Text))
			modbus.Write(183, 1, array)	 
		except ValueError as inst:
			print inst
			print self._textBox2.Text	
