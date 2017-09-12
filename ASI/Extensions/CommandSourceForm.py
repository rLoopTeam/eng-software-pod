
import System.Drawing
import System.Windows.Forms

from System.Drawing import *
from System.Windows.Forms import *
from globals import *
from System import *

class CommandSourceForm(Form):
	def __init__(self):
		self.InitializeComponent()
	
	def InitializeComponent(self):
		self._CommandSourceComboBox = System.Windows.Forms.ComboBox()
		self._label1 = System.Windows.Forms.Label()
		self._label2 = System.Windows.Forms.Label()
		self._BrakeSourceComboBox = System.Windows.Forms.ComboBox()
		self._NextButton = System.Windows.Forms.Button()
		self.SuspendLayout()
		# 
		# CommandSourceComboBox
		# 
		self._CommandSourceComboBox.FormattingEnabled = True
		self._CommandSourceComboBox.Items.AddRange(System.Array[System.Object](
			["Network",
			"Throttle",
			"Pedal Sensor",
			"Throttle and Pedal",
			"Throttle or Pedal"]))
		self._CommandSourceComboBox.Location = System.Drawing.Point(133, 51)
		self._CommandSourceComboBox.Name = "CommandSourceComboBox"
		self._CommandSourceComboBox.Size = System.Drawing.Size(121, 21)
		self._CommandSourceComboBox.TabIndex = 0
		self._CommandSourceComboBox.SelectedIndexChanged += self.CommandSourceComboBoxSelectedIndexChanged
		# 
		# label1
		# 
		self._label1.Location = System.Drawing.Point(27, 54)
		self._label1.Name = "label1"
		self._label1.Size = System.Drawing.Size(100, 21)
		self._label1.TabIndex = 1
		self._label1.Text = "Command Source"
		# 
		# label2
		# 
		self._label2.Location = System.Drawing.Point(27, 127)
		self._label2.Name = "label2"
		self._label2.Size = System.Drawing.Size(100, 21)
		self._label2.TabIndex = 3
		self._label2.Text = "Brake Source"
		# 
		# BrakeSourceComboBox
		# 
		self._BrakeSourceComboBox.FormattingEnabled = True
		self._BrakeSourceComboBox.Items.AddRange(System.Array[System.Object](
			["Brake 1",
			"Brake 2",
			"PFS",
			"Cruise",
			"LIN"]))
		self._BrakeSourceComboBox.Location = System.Drawing.Point(133, 124)
		self._BrakeSourceComboBox.Name = "BrakeSourceComboBox"
		self._BrakeSourceComboBox.Size = System.Drawing.Size(121, 21)
		self._BrakeSourceComboBox.TabIndex = 2
		self._BrakeSourceComboBox.SelectedIndexChanged += self.BrakeSourceComboBoxSelectedIndexChanged
		# 
		# NextButton
		# 
		self._NextButton.Location = System.Drawing.Point(132, 199)
		self._NextButton.Name = "NextButton"
		self._NextButton.Size = System.Drawing.Size(75, 23)
		self._NextButton.TabIndex = 4
		self._NextButton.Text = "Next"
		self._NextButton.UseVisualStyleBackColor = True
		self._NextButton.Click += self.Button1Click
		# 
		# CommandSourceForm
		# 
		self.ClientSize = System.Drawing.Size(292, 273)
		self.Controls.Add(self._NextButton)
		self.Controls.Add(self._label2)
		self.Controls.Add(self._BrakeSourceComboBox)
		self.Controls.Add(self._label1)
		self.Controls.Add(self._CommandSourceComboBox)
		self.Name = "CommandSourceForm"
		self.Text = "Command Source"

		self.Load += self.InitializeForm
		self.ResumeLayout(False)
		
	def InitializeForm(self, sender, e):
		if not self.DesignMode:
			self.Icon = ico;		
		array = Array[Int16](range(1))
		try:				    
			modbus.Read(208, 1, array)
			self._CommandSourceComboBox.SelectedIndex = array[0]
		except Exception as inst:
			print inst
			
		try:				    
			modbus.Read(248, 1, array)
			self._BrakeSourceComboBox.SelectedIndex = array[0]
		except Exception as inst:
			print inst

	def CommandSourceComboBoxSelectedIndexChanged(self, sender, e):
		array = Array[Int16](range(1))
		try:
			array[0] = int(self._CommandSourceComboBox.SelectedIndex)   
			modbus.Write(208, 1, array)
		except Exception as inst:
			print inst		
		
		if(array[0] == 0):
			self._NextButton.Enabled = False
		else:
			self._NextButton.Enabled = True
			
	def BrakeSourceComboBoxSelectedIndexChanged(self, sender, e):
		array = Array[Int16](range(1))
		try:
			array[0] = int(self._BrakeSourceComboBox.SelectedIndex)
			modbus.Write(248, 1, array)
		except Exception as inst:
			print inst					

	def Button1Click(self, sender, e):
		Help.ShowHelpIndex(self, "mspaint.chm");
		mode = self._CommandSourceComboBox.SelectedIndex
		if mode == 1 or mode == 3 or mode == 4:
			import ThrottleSetting
			f = ThrottleSetting.ThrottleSettingForm()
			f.ShowDialog()
		if mode == 2 or mode == 3 or mode == 4:
			import PedalSetting
			f = PedalSetting.PedalSensorSelectForm()
			f.ShowDialog()			