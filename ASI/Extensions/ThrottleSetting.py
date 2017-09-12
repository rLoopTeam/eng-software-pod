import sys
import time
import clr
clr.AddReference("System.Drawing")
clr.AddReference("System.Windows.Forms")
import System
from System import *
from System.Drawing import Point
from System.Windows.Forms import Application, Button, Form, Label
from globals import *

class ThrottleSettingForm(Form):
	def __init__(self):
	    self.InitializeComponent()
	
	def InitializeComponent(self):
		self._label1 = System.Windows.Forms.Label()
		self._label2 = System.Windows.Forms.Label()
		self._button1 = System.Windows.Forms.Button()
		self._button2 = System.Windows.Forms.Button()
		self._ClosedVoltageTextBox = System.Windows.Forms.TextBox()
		self._OpenVoltageTextBox = System.Windows.Forms.TextBox()
		self._groupBox1 = System.Windows.Forms.GroupBox()
		self._groupBox2 = System.Windows.Forms.GroupBox()
		self._groupBox1.SuspendLayout()
		self._groupBox2.SuspendLayout()
		self.SuspendLayout()
		# 
		# label1
		# 
		self._label1.Location = System.Drawing.Point(34, 16)
		self._label1.Name = "label1"
		self._label1.Size = System.Drawing.Size(110, 30)
		self._label1.TabIndex = 0
		self._label1.Text = "Leave Throttle fully closed, then CLICK1"
		# 
		# label2
		# 
		self._label2.Location = System.Drawing.Point(34, 16)
		self._label2.Name = "label2"
		self._label2.Size = System.Drawing.Size(110, 30)
		self._label2.TabIndex = 1
		self._label2.Text = "Twist Throttle fully open, then CLICK2"
		# 
		# button1
		# 
		self._button1.Location = System.Drawing.Point(34, 49)
		self._button1.Name = "button1"
		self._button1.Size = System.Drawing.Size(75, 23)
		self._button1.TabIndex = 2
		self._button1.Text = "CLICK1"
		self._button1.Click += self.button1Pressed
		# 
		# button2
		# 
		self._button2.Location = System.Drawing.Point(34, 49)
		self._button2.Name = "button2"
		self._button2.Size = System.Drawing.Size(75, 23)
		self._button2.TabIndex = 3
		self._button2.Text = "CLICK2"
		self._button2.Click += self.button2Pressed
		# 
		# ClosedVoltageTextBox
		# 
		self._ClosedVoltageTextBox.Enabled = False
		self._ClosedVoltageTextBox.Location = System.Drawing.Point(34, 78)
		self._ClosedVoltageTextBox.Name = "ClosedVoltageTextBox"
		self._ClosedVoltageTextBox.Size = System.Drawing.Size(75, 20)
		self._ClosedVoltageTextBox.TabIndex = 4
		# 
		# OpenVoltageTextBox
		# 
		self._OpenVoltageTextBox.Enabled = False
		self._OpenVoltageTextBox.Location = System.Drawing.Point(34, 78)
		self._OpenVoltageTextBox.Name = "OpenVoltageTextBox"
		self._OpenVoltageTextBox.Size = System.Drawing.Size(75, 20)
		self._OpenVoltageTextBox.TabIndex = 5
		# 
		# groupBox1
		# 
		self._groupBox1.Controls.Add(self._label1)
		self._groupBox1.Controls.Add(self._button1)
		self._groupBox1.Controls.Add(self._ClosedVoltageTextBox)
		self._groupBox1.Location = System.Drawing.Point(30, 12)
		self._groupBox1.Name = "groupBox1"
		self._groupBox1.Size = System.Drawing.Size(200, 109)
		self._groupBox1.TabIndex = 6
		self._groupBox1.TabStop = False
		self._groupBox1.Text = "Throttle Closed"
		# 
		# groupBox2
		# 
		self._groupBox2.Controls.Add(self._label2)
		self._groupBox2.Controls.Add(self._button2)
		self._groupBox2.Controls.Add(self._OpenVoltageTextBox)
		self._groupBox2.Location = System.Drawing.Point(30, 144)
		self._groupBox2.Name = "groupBox2"
		self._groupBox2.Size = System.Drawing.Size(200, 111)
		self._groupBox2.TabIndex = 7
		self._groupBox2.TabStop = False
		self._groupBox2.Text = "Throttle Open"
		# 
		# ThrottleSettingForm
		# 
		self.ClientSize = System.Drawing.Size(292, 273)
		self.Controls.Add(self._groupBox2)
		self.Controls.Add(self._groupBox1)
		self.Name = "ThrottleSettingForm"
		self.Text = "Throttle Setting"
		self.Load += self.InitializeForm
		self._groupBox1.ResumeLayout(False)
		self._groupBox1.PerformLayout()
		self._groupBox2.ResumeLayout(False)
		self._groupBox2.PerformLayout()
		self.ResumeLayout(False)
		
	def InitializeForm(self, sender, args) :
		if not self.DesignMode:
			self.Icon = ico;			
		array = Array[Int16](range(1))
		try:
			modbus.Read(213, 1, array) 
			self._OpenVoltageTextBox.Text = "{0:.2f}".format(array[0] / 4096.0)
		except Exception as inst:
			print inst			
			
		try:
			modbus.Read(214, 1, array) 
			self._ClosedVoltageTextBox.Text = "{0:.2f}".format(array[0] / 4096.0)
		except Exception as inst:
			print inst					
		
	def button1Pressed(self, sender, args):
		array = Array[Int16](range(1))
		modbus.Read(270, 1, array) 
		modbus.Write(214, 1, array)
		self._ClosedVoltageTextBox.Text = "{0:.2f}".format(array[0] / 4096.0)
	
	def button2Pressed(self, sender, args):
		array = Array[Int16](range(1))
		modbus.Read(270, 1, array) 
		modbus.Write(213, 1, array)
		self._OpenVoltageTextBox.Text = "{0:.2f}".format(array[0] / 4096.0)

