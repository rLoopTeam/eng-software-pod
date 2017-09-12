from System import *
import System.Drawing
import System.Windows.Forms

from System.Drawing import *
from System.Windows.Forms import *
import globals
from globals import *
#import MotorAutoTuning
import time

class BasicMotorSetUpForm(System.Windows.Forms.Form):
	def __init__(self):
	    self.InitializeComponent()
	
	def InitializeComponent(self):
		self._button1 = System.Windows.Forms.Button()
		self._label1 = System.Windows.Forms.Label()
		self._label2 = System.Windows.Forms.Label()
		self._label3 = System.Windows.Forms.Label()
		self._label4 = System.Windows.Forms.Label()
		self._label5 = System.Windows.Forms.Label()
		self._label6 = System.Windows.Forms.Label()
		self._label7 = System.Windows.Forms.Label()
		self._textBox1 = System.Windows.Forms.TextBox()
		self._textBox2 = System.Windows.Forms.TextBox()
		self._textBox3 = System.Windows.Forms.TextBox()
		self._textBox4 = System.Windows.Forms.TextBox()
		self._textBox5 = System.Windows.Forms.TextBox()
		self._textBox6 = System.Windows.Forms.TextBox()
		self._comboBox1 = System.Windows.Forms.ComboBox()
		self.SuspendLayout()
		# 
		# button1
		# 
		self._button1.Location = System.Drawing.Point(123, 219)
		self._button1.Name = "button1"
		self._button1.Size = System.Drawing.Size(121, 31)
		self._button1.TabIndex = 19
		self._button1.Text = "Go to Motor Autotune"
		self._button1.UseVisualStyleBackColor = True
		self._button1.Click += self.AutoTuneClicked
		# 
		# label1
		# 
		self._label1.AutoSize = True
		self._label1.Location = System.Drawing.Point(40, 24)
		self._label1.Name = "label1"
		self._label1.Size = System.Drawing.Size(101, 13)
		self._label1.TabIndex = 2
		self._label1.Text = "Rated motor current"
		# 
		# label2
		# 
		self._label2.AutoSize = True
		self._label2.Location = System.Drawing.Point(40, 46)
		self._label2.Name = "label2"
		self._label2.Size = System.Drawing.Size(97, 13)
		self._label2.TabIndex = 3
		self._label2.Text = "Rated motor power"
		# 
		# label3
		# 
		self._label3.AutoSize = True
		self._label3.Location = System.Drawing.Point(40, 68)
		self._label3.Name = "label3"
		self._label3.Size = System.Drawing.Size(97, 13)
		self._label3.TabIndex = 4
		self._label3.Text = "Rated motor speed"
		# 
		# label4
		# 
		self._label4.AutoSize = True
		self._label4.Location = System.Drawing.Point(40, 90)
		self._label4.Name = "label4"
		self._label4.Size = System.Drawing.Size(109, 13)
		self._label4.TabIndex = 5
		self._label4.Text = "Rated system voltage"
		# 
		# label5
		# 
		self._label5.AutoSize = True
		self._label5.Location = System.Drawing.Point(40, 112)
		self._label5.Name = "label5"
		self._label5.Size = System.Drawing.Size(103, 13)
		self._label5.TabIndex = 6
		self._label5.Text = "# of motor pole pairs"
		# 
		# label6
		# 
		self._label6.AutoSize = True
		self._label6.Location = System.Drawing.Point(40, 134)
		self._label6.Name = "label6"
		self._label6.Size = System.Drawing.Size(53, 13)
		self._label6.TabIndex = 7
		self._label6.Text = "Gear ratio"
		# 
		# label7
		# 
		self._label7.AutoSize = True
		self._label7.Location = System.Drawing.Point(40, 167)
		self._label7.Name = "label7"
		self._label7.Size = System.Drawing.Size(91, 13)
		self._label7.TabIndex = 8
		self._label7.Text = "Motor sensor type"
		# 
		# textBox1
		# 
		self._textBox1.Location = System.Drawing.Point(169, 24)
		self._textBox1.Name = "textBox1"
		self._textBox1.Size = System.Drawing.Size(44, 20)
		self._textBox1.TabIndex = 10
		self._textBox1.TextChanged += self._textBox1_TextChanged
		# 
		# textBox2
		# 
		self._textBox2.Location = System.Drawing.Point(169, 45)
		self._textBox2.Name = "textBox2"
		self._textBox2.Size = System.Drawing.Size(44, 20)
		self._textBox2.TabIndex = 11
		self._textBox2.TextChanged += self._textBox2_TextChanged
		# 
		# textBox3
		# 
		self._textBox3.Location = System.Drawing.Point(169, 66)
		self._textBox3.Name = "textBox3"
		self._textBox3.Size = System.Drawing.Size(44, 20)
		self._textBox3.TabIndex = 12
		self._textBox3.TextChanged += self._textBox3_TextChanged
		# 
		# textBox4
		# 
		self._textBox4.Location = System.Drawing.Point(169, 87)
		self._textBox4.Name = "textBox4"
		self._textBox4.Size = System.Drawing.Size(44, 20)
		self._textBox4.TabIndex = 13
		self._textBox4.TextChanged += self._textBox4_TextChanged
		# 
		# textBox5
		# 
		self._textBox5.Location = System.Drawing.Point(169, 108)
		self._textBox5.Name = "textBox5"
		self._textBox5.Size = System.Drawing.Size(44, 20)
		self._textBox5.TabIndex = 14
		self._textBox5.TextChanged += self._textBox5_TextChanged
		# 
		# textBox6
		# 
		self._textBox6.Location = System.Drawing.Point(169, 129)
		self._textBox6.Name = "textBox6"
		self._textBox6.Size = System.Drawing.Size(44, 20)
		self._textBox6.TabIndex = 15
		self._textBox6.TextChanged += self._textBox6_TextChanged
		# 
		# comboBox1
		# 
		self._comboBox1.Items.AddRange(System.Array[System.Object](
			["hall based",
			"hall start and sensorless run",
			"sensorless",
			"reserved"]))
		self._comboBox1.Location = System.Drawing.Point(169, 159)
		self._comboBox1.Name = "comboBox1"
		self._comboBox1.Size = System.Drawing.Size(103, 21)
		self._comboBox1.TabIndex = 0
		self._comboBox1.SelectedIndexChanged += self._comboBox1_SelectedIndexChanged
		# 
		# BasicMotorSetUpForm
		# 
		self.ClientSize = System.Drawing.Size(284, 262)
		self.Controls.Add(self._comboBox1)
		self.Controls.Add(self._textBox6)
		self.Controls.Add(self._textBox5)
		self.Controls.Add(self._textBox4)
		self.Controls.Add(self._textBox3)
		self.Controls.Add(self._textBox2)
		self.Controls.Add(self._textBox1)
		self.Controls.Add(self._label7)
		self.Controls.Add(self._label6)
		self.Controls.Add(self._label5)
		self.Controls.Add(self._label4)
		self.Controls.Add(self._label3)
		self.Controls.Add(self._label2)
		self.Controls.Add(self._label1)
		self.Controls.Add(self._button1)
		self.Name = "BasicMotorSetUpForm"
		self.Text = "Basic Motor Setup"
		self.Load += self.InitializeForm
		self.ResumeLayout(False)
		self.PerformLayout()
	
	def InitializeForm (self, sender, e):
		if not self.DesignMode:
			self.Icon = ico;			
		array = Array[Int16](range(1))
		try:
			modbus.Read(71, 1, array)
			self._textBox1.Text = str(array[0])
		except Exception as inst:
			print inst		

		try:
			modbus.Read(73, 1, array)
			self._textBox2.Text = str(array[0])
		except Exception as inst:
			print inst			

		try:
			modbus.Read(72, 1, array)
			self._textBox3.Text = str(array[0])
		except Exception as inst:
			print inst		
	    
		try:
			modbus.Read(70, 1, array)
			self._textBox4.Text = str(array[0])
		except Exception as inst:
			print inst	

		try:
			modbus.Read(78, 1, array)
			self._textBox5.Text = str(array[0])
		except Exception as inst:
			print inst	

		try:
			modbus.Read(226, 1, array)
			self._textBox6.Text = str(float(array[0])/256.0)
		except Exception as inst:
			print inst		
		try:		    
		    modbus.Read(77, 1, array)		
		    self._comboBox1.SelectedIndex = array[0]
		except Exception as inst:
			print inst
			
	def RunDiscoverMode3(self) :
		array = Array[Int16](range(1))
		array[0] = 3
		modbus.Write(481, 1, array)
		time.sleep(5)

		while (True):
			time.sleep(1)
			modbus.Read(313, 1, array)
			speed = array[0]
			if speed == 0:
				break
			
	def AutoTuneClicked (self, sender, e):
		array = Array[Int16](range(1))
		array[0] = 4
		modbus.Write(481, 1, array)
		time.sleep(3)
		array[0] = 4096
		modbus.Write(76, 1, array)
		
		self.RunDiscoverMode3()
			
		result = MessageBox.Show("Did the motor spin in the forward direction?", "Motor Direction", MessageBoxButtons.YesNo, MessageBoxIcon.Question) 
		if result == DialogResult.No:
			modbus.Read(127, 1, array)
			array[0] = array[0] ^ 1
			modbus.Write(127, 1, array)
			self.RunDiscoverMode3()
			
		modbus.Read(460, 1, array)
		modbus.Write(79, 1, array)
		
		for x in range(0, 7):
			modbus.Read(440 + x, 1, array)
			array[0] = array[0] / 4096
			modbus.Write(80 + x, 1, array)			
		
		modbus.Read(462, 1, array)
		ratedRPM = array[0]
		modbus.Read(72, 1, array)
		print "measured RPM: %d" % ratedRPM
		print "nominal RPM: %d" % array[0]
		modbus.Read(461, 1, array)
		print "measured Kv: %f" % (array[0]	/ 4096.0)
		
	def _textBox1_TextChanged(self, sender, e):
		try:
		    array = Array[Int16](range(1))
		    array[0] = int(float(self._textBox1.Text))
		    modbus.Write(71, 1, array)
		except ValueError as inst:
			print inst
			print self._textBox1.Text			
	
	def _textBox2_TextChanged(self, sender, e):
		try:
		    array = Array[Int16](range(1))
		    array[0] = int(float(self._textBox2.Text))
		    modbus.Write(73, 1, array)
		except ValueError as inst:
			print inst
			print self._textBox2.Text		
	
	def _textBox3_TextChanged(self, sender, e):
		try:
		    array = Array[Int16](range(1))
		    array[0] = int(float(self._textBox3.Text))
		    modbus.Write(72, 1, array)
		except ValueError as inst:
			print inst
			print self._textBox3.Text			
	
	def _textBox4_TextChanged(self, sender, e):
		try:
		    array = Array[Int16](range(1))
		    array[0] = int(float(self._textBox4.Text))
		    if(array[0] > 20):
		    	modbus.Write(70, 1, array)
		except ValueError as inst:
			print inst	
			print self._textBox4.Text			
	
	def _textBox5_TextChanged(self, sender, e):
		try:
		    array = Array[Int16](range(1))
		    array[0] = int(float(self._textBox5.Text))
		    modbus.Write(78, 1, array)
		except ValueError as inst:
			print inst
			print self._textBox5.Text			
	
	def _textBox6_TextChanged(self, sender, e):
		try:
			array = Array[Int16](range(1))
			array[0] = int(float(self._textBox6.Text)*256)
			modbus.Write(226, 1, array)
		except ValueError as inst:
			print inst
			print self._textBox6.Text			

	
	def _comboBox1_SelectedIndexChanged(self, sender, e):
	    array = Array[Int16](range(1))
	    array[0] = int(self._comboBox1.SelectedIndex)
	    modbus.Write(77, 1, array)

	    if array[0] == 2:
			modbus.Read(212, 1, array)
			array[0] = array[0] | 64
			modbus.Write(212, 1, array)
	    else:
			return

	def CheckedChanged(self, sender, e):
	    if sender.Text == "Yes":
			print "Yes"
	    else:
			print "No"     