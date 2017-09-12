from System import *
import System.Drawing
import System.Windows.Forms

from System.Drawing import *
from System.Windows.Forms import *

from globals import *

class VehicleConfigurationForm(Form):
	def __init__(self):
		self.InitializeComponent()
	
	def InitializeComponent(self):
		self._label1 = System.Windows.Forms.Label()
		self._label2 = System.Windows.Forms.Label()
		self._label3 = System.Windows.Forms.Label()
		self._MaximumSpeedTextBox = System.Windows.Forms.TextBox()
		self._WalkSpeedTextBox = System.Windows.Forms.TextBox()
		self._WheelSpeedSensorTextBox = System.Windows.Forms.TextBox()
		self._BoostSpeedTextBox = System.Windows.Forms.TextBox()
		self._label4 = System.Windows.Forms.Label()
		self._label5 = System.Windows.Forms.Label()
		self._BMSComboBox = System.Windows.Forms.ComboBox()
		self.SuspendLayout()
		# 
		# label1
		# 
		self._label1.Location = System.Drawing.Point(12, 32)
		self._label1.Name = "label1"
		self._label1.Size = System.Drawing.Size(126, 20)
		self._label1.TabIndex = 0
		self._label1.Text = "Maximum Speed"
		# 
		# label2
		# 
		self._label2.Location = System.Drawing.Point(12, 92)
		self._label2.Name = "label2"
		self._label2.Size = System.Drawing.Size(126, 21)
		self._label2.TabIndex = 1
		self._label2.Text = "Walk Speed"
		# 
		# label3
		# 
		self._label3.Location = System.Drawing.Point(12, 212)
		self._label3.Name = "label3"
		self._label3.Size = System.Drawing.Size(144, 20)
		self._label3.TabIndex = 2
		self._label3.Text = "Wheel Speed Sensor PPR"
		# 
		# MaximumSpeedTextBox
		# 
		self._MaximumSpeedTextBox.Location = System.Drawing.Point(189, 29)
		self._MaximumSpeedTextBox.Name = "MaximumSpeedTextBox"
		self._MaximumSpeedTextBox.Size = System.Drawing.Size(100, 20)
		self._MaximumSpeedTextBox.TabIndex = 3
		self._MaximumSpeedTextBox.TextChanged += self.MaximumSpeedTextBoxTextChanged
		# 
		# WalkSpeedTextBox
		# 
		self._WalkSpeedTextBox.Location = System.Drawing.Point(189, 89)
		self._WalkSpeedTextBox.Name = "WalkSpeedTextBox"
		self._WalkSpeedTextBox.Size = System.Drawing.Size(100, 20)
		self._WalkSpeedTextBox.TabIndex = 4
		self._WalkSpeedTextBox.TextChanged += self.WalkSpeedTextBoxTextChanged
		# 
		# WheelSpeedSensorTextBox
		# 
		self._WheelSpeedSensorTextBox.Location = System.Drawing.Point(189, 209)
		self._WheelSpeedSensorTextBox.Name = "WheelSpeedSensorTextBox"
		self._WheelSpeedSensorTextBox.Size = System.Drawing.Size(100, 20)
		self._WheelSpeedSensorTextBox.TabIndex = 5
		self._WheelSpeedSensorTextBox.TextChanged += self.WheelSpeedSensorTextBoxTextChanged
		# 
		# BoostSpeedTextBox
		# 
		self._BoostSpeedTextBox.Location = System.Drawing.Point(189, 149)
		self._BoostSpeedTextBox.Name = "BoostSpeedTextBox"
		self._BoostSpeedTextBox.Size = System.Drawing.Size(100, 20)
		self._BoostSpeedTextBox.TabIndex = 7
		self._BoostSpeedTextBox.TextChanged += self.BoostSpeedTextBoxTextChanged
		# 
		# label4
		# 
		self._label4.Location = System.Drawing.Point(12, 152)
		self._label4.Name = "label4"
		self._label4.Size = System.Drawing.Size(126, 21)
		self._label4.TabIndex = 6
		self._label4.Text = "Boost Speed"
		# 
		# label5
		# 
		self._label5.Location = System.Drawing.Point(12, 264)
		self._label5.Name = "label5"
		self._label5.Size = System.Drawing.Size(144, 20)
		self._label5.TabIndex = 8
		self._label5.Text = "BMS Type"
		# 
		# BMSComboBox
		# 
		self._BMSComboBox.FormattingEnabled = True
		self._BMSComboBox.Items.AddRange(System.Array[System.Object](
			["None",
			"Voltage Model",
			"0-10V",
			"Reserved",
			"LIN",
			"ASI Modbus"]))
		self._BMSComboBox.Location = System.Drawing.Point(189, 261)
		self._BMSComboBox.Name = "BMSComboBox"
		self._BMSComboBox.Size = System.Drawing.Size(100, 21)
		self._BMSComboBox.TabIndex = 9
		self._BMSComboBox.SelectedIndexChanged += self.ComboBox1SelectedIndexChanged
		# 
		# VehicleConfigurationForm
		# 
		self.ClientSize = System.Drawing.Size(318, 310)
		self.Controls.Add(self._BMSComboBox)
		self.Controls.Add(self._label5)
		self.Controls.Add(self._BoostSpeedTextBox)
		self.Controls.Add(self._label4)
		self.Controls.Add(self._WheelSpeedSensorTextBox)
		self.Controls.Add(self._WalkSpeedTextBox)
		self.Controls.Add(self._MaximumSpeedTextBox)
		self.Controls.Add(self._label3)
		self.Controls.Add(self._label2)
		self.Controls.Add(self._label1)
		self.Name = "VehicleConfigurationForm"
		self.Text = "Vehicle Configuration"
		self.Load += self.InitializeForm
		self.ResumeLayout(False)
		self.PerformLayout()
		
	def InitializeForm(self, sender, e):
		if not self.DesignMode:
			self.Icon = ico;			
		array = Array[Int16](range(1))
		try:
			modbus.Read(229, 1, array)
			self._MaximumSpeedTextBox.Text = "{0:.1f}".format(float(array[0]) / 256.0)
		except Exception as inst:
			print inst
			
		try:
			modbus.Read(230, 1, array)
			self._WalkSpeedTextBox.Text = "{0:.1f}".format(float(array[0]) / 256.0)
		except Exception as inst:
			print inst		

		try:
			modbus.Read(252, 1, array)
			self._BoostSpeedTextBox.Text = "{0:.1f}".format(float(array[0]) / 256.0)
		except Exception as inst:
			print inst		

		try:
			modbus.Read(234, 1, array)
			self._WheelSpeedSensorTextBox.Text = str(array[0])
		except Exception as inst:
			print inst		
			
		try :
			modbus.Read(209, 1, array)
			self._BMSComboBox.SelectedIndex = array[0]
		except Exception as inst:
			print inst			
			
	def MaximumSpeedTextBoxTextChanged(self, sender, e):
		try:
		    array = Array[Int16](range(1))
		    array[0] = int(float(self._MaximumSpeedTextBox.Text) * 256)
		    modbus.Write(229, 1, array)
		except ValueError as inst:
			print inst
			print self._MaximumSpeedTextBox.Text					    

	def WalkSpeedTextBoxTextChanged(self, sender, e):
		try:
		    array = Array[Int16](range(1))
		    array[0] = int(float(self._WalkSpeedTextBox.Text) * 256)
		    modbus.Write(230, 1, array)
		except ValueError as inst:
			print inst
			print self._WalkSpeedTextBox.Text
			
		modbus.Read(212, 1, array)
		if array[0] != 0:
			array[0] = array[0] | 2048
		else:
			array[0] = array[0] & ~2048
		modbus.Write(212, 1, array)

	def WheelSpeedSensorTextBoxTextChanged(self, sender, e):
		try:
		    array = Array[Int16](range(1))
		    array[0] = int(self._WheelSpeedSensorTextBox.Text)
		    modbus.Write(234, 1, array)
		except ValueError as inst:
			print inst
			print self._WheelSpeedSensorTextBox.Text		    

	def BoostSpeedTextBoxTextChanged(self, sender, e):
		try:
		    array = Array[Int16](range(1))
		    array[0] = int(float(self._BoostSpeedTextBox.Text) * 256)
		    modbus.Write(252, 1, array)
		except ValueError as inst:
			print inst
			print self._BoostSpeedTextBox.Text		 		    
		modbus.Read(212, 1, array)
		if array[0] != 0:
			array[0] = array[0] | 2048
		else:
			array[0] = array[0] & ~2048
		modbus.Write(212, 1, array)	    

	def ComboBox1SelectedIndexChanged(self, sender, e):
		array = Array[Int16](range(1))
		array[0] = int(self._BMSComboBox.SelectedIndex)
		modbus.Write(209, 1, array)