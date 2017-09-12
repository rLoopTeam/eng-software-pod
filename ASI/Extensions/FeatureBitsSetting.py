import sys
import time
import clr
clr.AddReference("System.Drawing")
clr.AddReference("System.Windows.Forms")
clr.AddReference("ModBusLib")

import System
from System import *
from System.Windows.Forms import *
from System.ComponentModel import *
from System.Drawing import *
from clr import *
from globals import *

class FeaturesAddingForm(Form):
	def __init__(self):
	    self.InitializeComponent()
	
	def InitializeComponent(self):
		self._checkBox1 = System.Windows.Forms.CheckBox()
		self._checkBox2 = System.Windows.Forms.CheckBox()
		self._checkBox3 = System.Windows.Forms.CheckBox()
		self._checkBox4 = System.Windows.Forms.CheckBox()
		self._checkBox5 = System.Windows.Forms.CheckBox()
		self._checkBox6 = System.Windows.Forms.CheckBox()
		self._checkBox7 = System.Windows.Forms.CheckBox()
		self._checkBox8 = System.Windows.Forms.CheckBox()
		self._checkBox9 = System.Windows.Forms.CheckBox()
		self._checkBox10 = System.Windows.Forms.CheckBox()
		self._checkBox11 = System.Windows.Forms.CheckBox()
		self._checkBox12 = System.Windows.Forms.CheckBox()
		self._groupBox1 = System.Windows.Forms.GroupBox()
		self._groupBox1.SuspendLayout()
		self.SuspendLayout()
		# 
		# checkBox1
		# 
		self._checkBox1.AutoSize = True
		self._checkBox1.Location = System.Drawing.Point(31, 25)
		self._checkBox1.Name = "checkBox1"
		self._checkBox1.Size = System.Drawing.Size(75, 17)
		self._checkBox1.TabIndex = 0
		self._checkBox1.Text = "Freewheel"
		self._checkBox1.UseVisualStyleBackColor = True
		self._checkBox1.CheckedChanged += self._checkBox_CheckedChanged
		# 
		# checkBox2
		# 
		self._checkBox2.AutoSize = True
		self._checkBox2.Location = System.Drawing.Point(31, 55)
		self._checkBox2.Name = "checkBox2"
		self._checkBox2.Size = System.Drawing.Size(89, 17)
		self._checkBox2.TabIndex = 1
		self._checkBox2.Text = "Drive reverse"
		self._checkBox2.UseVisualStyleBackColor = True
		self._checkBox2.CheckedChanged += self._checkBox_CheckedChanged
		# 
		# checkBox3
		# 
		self._checkBox3.AutoSize = True
		self._checkBox3.Location = System.Drawing.Point(31, 85)
		self._checkBox3.Name = "checkBox3"
		self._checkBox3.Size = System.Drawing.Size(96, 17)
		self._checkBox3.TabIndex = 2
		self._checkBox3.Text = "Anti-theft alarm"
		self._checkBox3.UseVisualStyleBackColor = True
		self._checkBox3.CheckedChanged += self._checkBox_CheckedChanged
		# 
		# checkBox4
		# 
		self._checkBox4.AutoSize = True
		self._checkBox4.Location = System.Drawing.Point(31, 115)
		self._checkBox4.Name = "checkBox4"
		self._checkBox4.Size = System.Drawing.Size(99, 17)
		self._checkBox4.TabIndex = 3
		self._checkBox4.Text = "Low SOC alarm"
		self._checkBox4.UseVisualStyleBackColor = True
		self._checkBox4.CheckedChanged += self._checkBox_CheckedChanged
		# 
		# checkBox5
		# 
		self._checkBox5.AutoSize = True
		self._checkBox5.Location = System.Drawing.Point(31, 145)
		self._checkBox5.Name = "checkBox5"
		self._checkBox5.Size = System.Drawing.Size(89, 17)
		self._checkBox5.TabIndex = 4
		self._checkBox5.Text = "Analog brake"
		self._checkBox5.UseVisualStyleBackColor = True
		self._checkBox5.CheckedChanged += self._checkBox_CheckedChanged
		# 
		# checkBox6
		# 
		self._checkBox6.AutoSize = True
		self._checkBox6.Location = System.Drawing.Point(31, 175)
		self._checkBox6.Name = "checkBox6"
		self._checkBox6.Size = System.Drawing.Size(101, 17)
		self._checkBox6.TabIndex = 5
		self._checkBox6.Text = "Motor thermistor"
		self._checkBox6.UseVisualStyleBackColor = True
		self._checkBox6.CheckedChanged += self._checkBox_CheckedChanged
		# 
		# checkBox7
		# 
		self._checkBox7.AutoSize = True
		self._checkBox7.Location = System.Drawing.Point(165, 25)
		self._checkBox7.Name = "checkBox7"
		self._checkBox7.Size = System.Drawing.Size(109, 17)
		self._checkBox7.TabIndex = 6
		self._checkBox7.Text = "Motor stall shutoff"
		self._checkBox7.UseVisualStyleBackColor = True
		self._checkBox7.CheckedChanged += self._checkBox_CheckedChanged
		# 
		# checkBox8
		# 
		self._checkBox8.AutoSize = True
		self._checkBox8.Location = System.Drawing.Point(165, 55)
		self._checkBox8.Name = "checkBox8"
		self._checkBox8.Size = System.Drawing.Size(95, 17)
		self._checkBox8.TabIndex = 7
		self._checkBox8.Text = "Inverted brake"
		self._checkBox8.UseVisualStyleBackColor = True
		self._checkBox8.CheckedChanged += self._checkBox_CheckedChanged
		# 
		# checkBox9
		# 
		self._checkBox9.AutoSize = True
		self._checkBox9.Location = System.Drawing.Point(165, 85)
		self._checkBox9.Name = "checkBox9"
		self._checkBox9.Size = System.Drawing.Size(120, 17)
		self._checkBox9.TabIndex = 8
		self._checkBox9.Text = "Alternate speed limit"
		self._checkBox9.UseVisualStyleBackColor = True
		self._checkBox9.CheckedChanged += self._checkBox_CheckedChanged
		# 
		# checkBox10
		# 
		self._checkBox10.AutoSize = True
		self._checkBox10.Location = System.Drawing.Point(165, 115)
		self._checkBox10.Name = "checkBox10"
		self._checkBox10.Size = System.Drawing.Size(81, 17)
		self._checkBox10.TabIndex = 9
		self._checkBox10.Text = "Rolling start"
		self._checkBox10.UseVisualStyleBackColor = True
		self._checkBox10.CheckedChanged += self._checkBox_CheckedChanged
		# 
		# checkBox11
		# 
		self._checkBox11.AutoSize = True
		self._checkBox11.Location = System.Drawing.Point(165, 145)
		self._checkBox11.Name = "checkBox11"
		self._checkBox11.Size = System.Drawing.Size(72, 17)
		self._checkBox11.TabIndex = 10
		self._checkBox11.Text = "Reserved"
		self._checkBox11.UseVisualStyleBackColor = True
		self._checkBox11.CheckedChanged += self._checkBox_CheckedChanged
		# 
		# checkBox12
		# 
		self._checkBox12.AutoSize = True
		self._checkBox12.Location = System.Drawing.Point(165, 175)
		self._checkBox12.Name = "checkBox12"
		self._checkBox12.Size = System.Drawing.Size(80, 17)
		self._checkBox12.TabIndex = 11
		self._checkBox12.Text = "Walk mode"
		self._checkBox12.UseVisualStyleBackColor = True
		self._checkBox12.CheckedChanged += self._checkBox_CheckedChanged
		# 
		# groupBox1
		# 
		self._groupBox1.Controls.Add(self._checkBox12)
		self._groupBox1.Controls.Add(self._checkBox11)
		self._groupBox1.Controls.Add(self._checkBox10)
		self._groupBox1.Controls.Add(self._checkBox9)
		self._groupBox1.Controls.Add(self._checkBox8)
		self._groupBox1.Controls.Add(self._checkBox7)
		self._groupBox1.Controls.Add(self._checkBox6)
		self._groupBox1.Controls.Add(self._checkBox5)
		self._groupBox1.Controls.Add(self._checkBox4)
		self._groupBox1.Controls.Add(self._checkBox3)
		self._groupBox1.Controls.Add(self._checkBox2)
		self._groupBox1.Controls.Add(self._checkBox1)
		self._groupBox1.Location = System.Drawing.Point(13, 13)
		self._groupBox1.Name = "groupBox1"
		self._groupBox1.Size = System.Drawing.Size(307, 206)
		self._groupBox1.TabIndex = 12
		self._groupBox1.TabStop = False
		self._groupBox1.Text = "eBike Features"
		# 
		# FeaturesAddingForm
		# 
		self.ClientSize = System.Drawing.Size(329, 237)
		self.Controls.Add(self._groupBox1)
		self.Name = "FeaturesAddingForm"
		self.Text = "eBike Features"
		self.Load += self.InitializeForm
		self._groupBox1.ResumeLayout(False)
		self._groupBox1.PerformLayout()
		self.ResumeLayout(False)
	
	def InitializeForm(self, sender, e):
		if not self.DesignMode:
			self.Icon = ico;
		a = [self._checkBox1, self._checkBox2, self._checkBox3, self._checkBox4, self._checkBox5, self._checkBox6, self._checkBox7, self._checkBox8, self._checkBox9, self._checkBox10, self._checkBox11, self._checkBox12]			
		array = Array[Int16](range(1))
		modbus.Read(212, 1, array)
		i = 0
		features = array[0]
		try :
			for item in a:				
				if ((features & (1 << i)) == (1 << i)):
					item.Checked = True
				else:
					item.Checked = False
				i = i + 1
		except Exception as inst:
			print inst

	def _checkBox_CheckedChanged(self, sender, e):
		if not sender.Checked and not self.DesignMode:
			array = Array[Int16](range(1))
			modbus.Read(212, 1, array)
			temp = int(sender.TabIndex)
			array[0] &= ~2**temp
			modbus.Write(212, 1, array)
		elif not self.DesignMode:
			array = Array[Int16](range(1))
			modbus.Read(212, 1, array)
			temp = int(sender.TabIndex)
			array[0] |= 2**temp
			modbus.Write(212, 1, array)
			
	def _button1_Click(self, sender, e):
		array = Array[Int16](range(1))
		modbus.Read(212, 1, array)
	       
