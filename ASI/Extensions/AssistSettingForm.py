import sys
import time
import clr
clr.AddReference("System.Drawing")
clr.AddReference("System.Windows.Forms")

import System
from System import *
from System import Array
from System.Windows.Forms import *
from System.ComponentModel import *
from System.Drawing import *
from clr import *
import globals
from globals import *

class AssistSettingForm(System.Windows.Forms.Form):
	def __init__(self):
	    self.InitializeComponent()
	
	def InitializeComponent(self):
		self._label1 = System.Windows.Forms.Label()
		self._label4 = System.Windows.Forms.Label()
		self._label5 = System.Windows.Forms.Label()
		self._comboBox1 = System.Windows.Forms.ComboBox()
		self._textBox3 = System.Windows.Forms.TextBox()
		self._textBox4 = System.Windows.Forms.TextBox()
		self._label6 = System.Windows.Forms.Label()
		self._label7 = System.Windows.Forms.Label()
		self._textBox5 = System.Windows.Forms.TextBox()
		self._textBox6 = System.Windows.Forms.TextBox()
		self._ReservedGroupBox = System.Windows.Forms.GroupBox()
		self._button1 = System.Windows.Forms.Button()
		self._button2 = System.Windows.Forms.Button()
		self._textBox1 = System.Windows.Forms.TextBox()
		self._AnalogOnlyGroup = System.Windows.Forms.GroupBox()
		self._AnalogLowTextBox = System.Windows.Forms.TextBox()
		self._AnalogHighTextBox = System.Windows.Forms.TextBox()
		self._HighAssistSpeed = System.Windows.Forms.TextBox()
		self._HighAssistGain = System.Windows.Forms.TextBox()
		self._ASIGroupBox = System.Windows.Forms.GroupBox()
		self._label2 = System.Windows.Forms.Label()
		self._label3 = System.Windows.Forms.Label()
		self._groupBox1 = System.Windows.Forms.GroupBox()
		self._ReservedGroupBox.SuspendLayout()
		self._AnalogOnlyGroup.SuspendLayout()
		self._ASIGroupBox.SuspendLayout()
		self._groupBox1.SuspendLayout()
		self.SuspendLayout()
		# 
		# label1
		# 
		self._label1.AutoSize = True
		self._label1.Location = System.Drawing.Point(41, 23)
		self._label1.Name = "label1"
		self._label1.Size = System.Drawing.Size(98, 13)
		self._label1.TabIndex = 0
		self._label1.Text = "Assist mode source"
		# 
		# label4
		# 
		self._label4.AutoSize = True
		self._label4.Location = System.Drawing.Point(20, 18)
		self._label4.Name = "label4"
		self._label4.Size = System.Drawing.Size(93, 13)
		self._label4.TabIndex = 3
		self._label4.Text = "Assist gain low (%)"
		# 
		# label5
		# 
		self._label5.AutoSize = True
		self._label5.Location = System.Drawing.Point(11, 53)
		self._label5.Name = "label5"
		self._label5.Size = System.Drawing.Size(102, 13)
		self._label5.TabIndex = 4
		self._label5.Text = "Assist speed low (%)"
		# 
		# comboBox1
		# 
		self._comboBox1.FormattingEnabled = True
		self._comboBox1.Items.AddRange(System.Array[System.Object](
			["None",
			"Analog on Brake2",
			"Reserved",
			"ASI Modbus",
			"LIN"]))
		self._comboBox1.Location = System.Drawing.Point(145, 20)
		self._comboBox1.Name = "comboBox1"
		self._comboBox1.Size = System.Drawing.Size(160, 21)
		self._comboBox1.TabIndex = 7
		self._comboBox1.SelectedIndexChanged += self._comboBox1_SelectedIndexChanged
		# 
		# textBox3
		# 
		self._textBox3.Location = System.Drawing.Point(141, 18)
		self._textBox3.Name = "textBox3"
		self._textBox3.Size = System.Drawing.Size(138, 20)
		self._textBox3.TabIndex = 10
		self._textBox3.TextChanged += self._textBox3_TextChanged
		# 
		# textBox4
		# 
		self._textBox4.Location = System.Drawing.Point(141, 50)
		self._textBox4.Name = "textBox4"
		self._textBox4.Size = System.Drawing.Size(138, 20)
		self._textBox4.TabIndex = 11
		self._textBox4.TextChanged += self._textBox4_TextChanged
		# 
		# label6
		# 
		self._label6.AutoSize = True
		self._label6.Location = System.Drawing.Point(18, 22)
		self._label6.Name = "label6"
		self._label6.Size = System.Drawing.Size(96, 13)
		self._label6.TabIndex = 5
		self._label6.Text = "Assist gain medium"
		# 
		# label7
		# 
		self._label7.AutoSize = True
		self._label7.Location = System.Drawing.Point(9, 54)
		self._label7.Name = "label7"
		self._label7.Size = System.Drawing.Size(105, 13)
		self._label7.TabIndex = 6
		self._label7.Text = "Assist speed medium"
		# 
		# textBox5
		# 
		self._textBox5.Location = System.Drawing.Point(142, 19)
		self._textBox5.Name = "textBox5"
		self._textBox5.Size = System.Drawing.Size(138, 20)
		self._textBox5.TabIndex = 12
		self._textBox5.TextChanged += self._textBox5_TextChanged
		# 
		# textBox6
		# 
		self._textBox6.Location = System.Drawing.Point(142, 51)
		self._textBox6.Name = "textBox6"
		self._textBox6.Size = System.Drawing.Size(138, 20)
		self._textBox6.TabIndex = 13
		self._textBox6.TextChanged += self._textBox6_TextChanged
		# 
		# ReservedGroupBox
		# 
		self._ReservedGroupBox.Controls.Add(self._textBox6)
		self._ReservedGroupBox.Controls.Add(self._textBox5)
		self._ReservedGroupBox.Controls.Add(self._label6)
		self._ReservedGroupBox.Controls.Add(self._label7)
		self._ReservedGroupBox.Location = System.Drawing.Point(25, 297)
		self._ReservedGroupBox.Name = "ReservedGroupBox"
		self._ReservedGroupBox.Size = System.Drawing.Size(306, 95)
		self._ReservedGroupBox.TabIndex = 19
		self._ReservedGroupBox.TabStop = False
		self._ReservedGroupBox.Text = "Reserved, ASI, and LIN Only"
		# 
		# button1
		# 
		self._button1.Location = System.Drawing.Point(22, 31)
		self._button1.Name = "button1"
		self._button1.Size = System.Drawing.Size(139, 34)
		self._button1.TabIndex = 1
		self._button1.Text = "Read assist voltage (low level assist mode)"
		self._button1.UseVisualStyleBackColor = True
		self._button1.Click += self._button1_Click
		# 
		# button2
		# 
		self._button2.Location = System.Drawing.Point(22, 71)
		self._button2.Name = "button2"
		self._button2.Size = System.Drawing.Size(139, 34)
		self._button2.TabIndex = 2
		self._button2.Text = "Read assist voltage (high level assist mode)"
		self._button2.UseVisualStyleBackColor = True
		self._button2.Click += self._button2_Click
		# 
		# textBox1
		# 
		self._textBox1.Location = System.Drawing.Point(173, 38)
		self._textBox1.Name = "textBox1"
		self._textBox1.Size = System.Drawing.Size(100, 20)
		self._textBox1.TabIndex = 3
		# 
		# AnalogOnlyGroup
		# 
		self._AnalogOnlyGroup.Controls.Add(self._AnalogHighTextBox)
		self._AnalogOnlyGroup.Controls.Add(self._AnalogLowTextBox)
		self._AnalogOnlyGroup.Controls.Add(self._button1)
		self._AnalogOnlyGroup.Controls.Add(self._button2)
		self._AnalogOnlyGroup.Location = System.Drawing.Point(25, 67)
		self._AnalogOnlyGroup.Name = "AnalogOnlyGroup"
		self._AnalogOnlyGroup.Size = System.Drawing.Size(305, 121)
		self._AnalogOnlyGroup.TabIndex = 20
		self._AnalogOnlyGroup.TabStop = False
		self._AnalogOnlyGroup.Text = "Analog Only"
		# 
		# AnalogLowTextBox
		# 
		self._AnalogLowTextBox.Enabled = False
		self._AnalogLowTextBox.Location = System.Drawing.Point(167, 39)
		self._AnalogLowTextBox.Name = "AnalogLowTextBox"
		self._AnalogLowTextBox.Size = System.Drawing.Size(113, 20)
		self._AnalogLowTextBox.TabIndex = 3
		# 
		# AnalogHighTextBox
		# 
		self._AnalogHighTextBox.Enabled = False
		self._AnalogHighTextBox.Location = System.Drawing.Point(167, 79)
		self._AnalogHighTextBox.Name = "AnalogHighTextBox"
		self._AnalogHighTextBox.Size = System.Drawing.Size(113, 20)
		self._AnalogHighTextBox.TabIndex = 4
		# 
		# HighAssistSpeed
		# 
		self._HighAssistSpeed.Location = System.Drawing.Point(142, 51)
		self._HighAssistSpeed.Name = "HighAssistSpeed"
		self._HighAssistSpeed.Size = System.Drawing.Size(138, 20)
		self._HighAssistSpeed.TabIndex = 13
		self._HighAssistSpeed.TextChanged += self.TextBox2TextChanged
		# 
		# HighAssistGain
		# 
		self._HighAssistGain.Location = System.Drawing.Point(142, 19)
		self._HighAssistGain.Name = "HighAssistGain"
		self._HighAssistGain.Size = System.Drawing.Size(138, 20)
		self._HighAssistGain.TabIndex = 12
		self._HighAssistGain.TextChanged += self.TextBox7TextChanged
		# 
		# ASIGroupBox
		# 
		self._ASIGroupBox.Controls.Add(self._HighAssistSpeed)
		self._ASIGroupBox.Controls.Add(self._HighAssistGain)
		self._ASIGroupBox.Controls.Add(self._label2)
		self._ASIGroupBox.Controls.Add(self._label3)
		self._ASIGroupBox.Location = System.Drawing.Point(25, 413)
		self._ASIGroupBox.Name = "ASIGroupBox"
		self._ASIGroupBox.Size = System.Drawing.Size(306, 95)
		self._ASIGroupBox.TabIndex = 21
		self._ASIGroupBox.TabStop = False
		self._ASIGroupBox.Text = "ASI, and LIN Only"
		# 
		# label2
		# 
		self._label2.AutoSize = True
		self._label2.Location = System.Drawing.Point(18, 22)
		self._label2.Name = "label2"
		self._label2.Size = System.Drawing.Size(80, 13)
		self._label2.TabIndex = 5
		self._label2.Text = "Assist gain high"
		# 
		# label3
		# 
		self._label3.AutoSize = True
		self._label3.Location = System.Drawing.Point(9, 54)
		self._label3.Name = "label3"
		self._label3.Size = System.Drawing.Size(89, 13)
		self._label3.TabIndex = 6
		self._label3.Text = "Assist speed high"
		# 
		# groupBox1
		# 
		self._groupBox1.Controls.Add(self._textBox4)
		self._groupBox1.Controls.Add(self._textBox3)
		self._groupBox1.Controls.Add(self._label5)
		self._groupBox1.Controls.Add(self._label4)
		self._groupBox1.Location = System.Drawing.Point(26, 194)
		self._groupBox1.Name = "groupBox1"
		self._groupBox1.Size = System.Drawing.Size(304, 93)
		self._groupBox1.TabIndex = 22
		self._groupBox1.TabStop = False
		self._groupBox1.Text = "All Assist Modes"
		# 
		# AssistSettingForm
		# 
		self.ClientSize = System.Drawing.Size(360, 534)
		self.Controls.Add(self._groupBox1)
		self.Controls.Add(self._ASIGroupBox)
		self.Controls.Add(self._AnalogOnlyGroup)
		self.Controls.Add(self._ReservedGroupBox)
		self.Controls.Add(self._comboBox1)
		self.Controls.Add(self._label1)
		self.Name = "AssistSettingForm"
		self.Text = "Assist Setting"
		self.Load += self.InitializeForm
		self._ReservedGroupBox.ResumeLayout(False)
		self._ReservedGroupBox.PerformLayout()
		self._AnalogOnlyGroup.ResumeLayout(False)
		self._AnalogOnlyGroup.PerformLayout()
		self._ASIGroupBox.ResumeLayout(False)
		self._ASIGroupBox.PerformLayout()
		self._groupBox1.ResumeLayout(False)
		self._groupBox1.PerformLayout()
		self.ResumeLayout(False)
		self.PerformLayout()
	
	def InitializeForm(self, sender, e):
		if not self.DesignMode:
			self.Icon = ico;	
			
		array = Array[Int16](range(1))
		try :
			modbus.Read(210, 1, array)
			self._comboBox1.SelectedIndex = array[0]
		except Exception as inst:
			print inst
		
		try :
			array = Array[Int16](range(1))
			modbus.Read(219, 1, array)
			self._textBox3.Text = "{0:.0f}".format(array[0] / 40.96)
		except Exception as inst:
			print inst
			
		try :
			modbus.Read(241, 1, array)
			self._textBox4.Text = "{0:.0f}".format(array[0] / 40.96)
		except Exception as e:
			print e
			
		try :
			modbus.Read(245, 1, array)
			self._textBox5.Text = "{0:.0f}".format(array[0] / 40.96)
		except Exception as e:
			print e		
			
		try :
			modbus.Read(246, 1, array)
			self._textBox6.Text = "{0:.0f}".format(array[0] / 40.96)
		except Exception as e:
			print e		
	
		try :
			modbus.Read(250, 1, array)
			self._HighAssistGain.Text = "{0:.0f}".format(array[0] / 40.96)
		except Exception as e:
			print e		
			
		try :
			modbus.Read(251, 1, array)
			self._HighAssistSpeed.Text = "{0:.0f}".format(array[0] / 40.96)
		except Exception as e:
			print e					
		
		try:
			modbus.Read(218, 1, array)
			self._AnalogLowTextBox.Text = "{0:.2f}".format(array[0] / 4096.0)
		except Exception as e:
			print e
			
		try:
			modbus.Read(217, 1, array)
			self._AnalogHighTextBox.Text = "{0:.2f}".format(array[0] / 4096.0)
		except Exception as e:
			print e				
	
	def _comboBox1_SelectedIndexChanged(self, sender, e):
		array = Array[Int16](range(1))
		array[0] = int(self._comboBox1.SelectedIndex)
		try:
			if array[0] == 0:
				self._groupBox1.Enabled = False
			else:
				self._groupBox1.Enabled = True
				
			if array[0] == 1:
				self._AnalogOnlyGroup.Enabled = True
			else:
				self._AnalogOnlyGroup.Enabled = False
				
			if array[0] == 2 or array[0] == 3 or array[0] == 4 :
				self._ReservedGroupBox.Enabled = True
			else:
				self._ReservedGroupBox.Enabled = False
				
			if array[0] == 3 or array[0] == 4 :
				self._ASIGroupBox.Enabled = True
			else:
				self._ASIGroupBox.Enabled = False				
			
			modbus.Write(210, 1, array)
		except Exception as e:
			print e
			
	
	
	def _textBox3_TextChanged(self, sender, e):
		try:
			array = Array[Int16](range(1))
			array[0] = int(float(self._textBox3.Text)*40.96)
			modbus.Write(219, 1, array)
		except ValueError as inst:
			print inst
			print self._textBox3.Text				
	
	def _textBox4_TextChanged(self, sender, e):
		try:
			array = Array[Int16](range(1))
			array[0] = int(float(self._textBox4.Text)*40.96)
			modbus.Write(241, 1, array)
		except ValueError as inst:
			print inst
			print self._textBox4.Text			    
	
	def _textBox5_TextChanged(self, sender, e):
		try:
		    array = Array[Int16](range(1))
		    array[0] = int(float(self._textBox5.Text)*40.96)
		    modbus.Write(245, 1, array)
		except ValueError as inst:
			print inst
			print self._textBox5.Text		   
	
	def _textBox6_TextChanged(self, sender, e):
		try:
		    array = Array[Int16](range(1))
		    array[0] = int(float(self._textBox6.Text)*40.96)
		    modbus.Write(246, 1, array)
		except ValueError as inst:
			print inst
			print self._textBox6.Text	
	
	def _button1_Click(self, sender, e):
		array = Array[Int16](range(1))
		modbus.Read(272, 1, array)
		modbus.Write(218, 1, array)
		self._AnalogLowTextBox.Text = "{0:.2f}".format(array[0] / 4096.0)
		
	def _button2_Click(self, sender, e):
		array = Array[Int16](range(1))
		modbus.Read(272, 1, array)
		modbus.Write(217, 1, array)
		self._AnalogHighTextBox.Text = "{0:.2f}".format(array[0] / 4096.0)
		
	def TextBox7TextChanged(self, sender, e):
		try:
			array = Array[Int16](range(1))
			array[0] = int(float(self._HighAssistGain.Text)*40.96)
			modbus.Write(250, 1, array)
		except ValueError as inst:
			print inst
			print self._textBox7.Text				
	
	def TextBox2TextChanged(self, sender, e):
		try:
		    array = Array[Int16](range(1))
		    array[0] = int(float(self._HighAssistSpeed.Text)*40.96)
		    modbus.Write(251, 1, array)
		except ValueError as inst:
			print inst
			print self._textBox2.Text			    