Namespace SIL3.rLoop.rPodControl.Panels.FlightControl

    ''' <summary>
    ''' Top level Flight Control
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Top

#Region "MEMBERS"
        ''' <summary>
        ''' Our application explorer bar
        ''' </summary>
        ''' <remarks></remarks>
        Private m_pExplorer As SIL3.ApplicationSupport.ExplorerBarHelper

        ''' <summary>
        ''' The index of our category in the explorer bar
        ''' </summary>
        ''' <remarks></remarks>
        Private m_iBarIndex As Integer

        ''' <summary>
        ''' SpaceX required telemetry from the FCU
        ''' </summary>
        Private m_pnlFlight__SpaceX As SIL3.rLoop.rPodControl.Panels.FlightControl.SpaceX

        ''' <summary>
        ''' Mission control page
        ''' </summary>
        Private m_pnlFlight__Mission As SIL3.rLoop.rPodControl.Panels.FlightControl.Mission

        ''' <summary>
        ''' Total system fault flags
        ''' </summary>
        Private m_pnlFlight__FaultFlags As SIL3.rLoop.rPodControl.Panels.FlightControl.Faults


        ''' <summary>
        ''' Accelerometer control panel
        ''' </summary>
        Private m_pnlFlight__Accel As SIL3.rLoop.rPodControl.Panels.FlightControl.Accelerometers

        ''' <summary>
        ''' Contrast sensors
        ''' </summary>
        Private m_pnlFlight__Contrast As SIL3.rLoop.rPodControl.Panels.FlightControl.Contrast

        ''' <summary>
        ''' Opto NCDT iF
        ''' </summary>
        Private m_pnlFlight__OptoNCDT As SIL3.rLoop.rPodControl.Panels.FlightControl.OptoNCDT

        ''' <summary>
        ''' Laser distance sensor
        ''' </summary>
        Private m_pnlFlight__LaserDist As SIL3.rLoop.rPodControl.Panels.FlightControl.LaserDistance

        ''' <summary>
        ''' Brakes system
        ''' </summary>
        Private m_pnlFlight__Brakes As SIL3.rLoop.rPodControl.Panels.FlightControl.Brakes

        ''' <summary>
        ''' Stepper drive system
        ''' </summary>
        Private m_pnlFlight__Stepper As SIL3.rLoop.rPodControl.Panels.FlightControl.Stepper

        ''' <summary>
        ''' ASI interface
        ''' </summary>
        Private m_pnlFlight__ASI As SIL3.rLoop.rPodControl.Panels.FlightControl.ASI

        ''' <summary>
        ''' Throttles page
        ''' </summary>
        Private m_pnlFlight__Throttle As SIL3.rLoop.rPodControl.Panels.FlightControl.Throttle

        ''' <summary>
        ''' Pusher interface
        ''' </summary>
        Private m_pnlFlight__Pusher As SIL3.rLoop.rPodControl.Panels.FlightControl.Pusher

		Private m_pnlFlight__TrackDB_Create As SIL3.rLoop.rPodControl.Panels.FlightControl.TrackDatabase.Creator
		Private m_pnlFlight__TrackDB_Monitor As SIL3.rLoop.rPodControl.Panels.FlightControl.TrackDatabase.Monitor

        Private m_pnlFlight__Geometry As SIL3.rLoop.rPodControl.Panels.FlightControl.Geometry

        ''' <summary>
        ''' The logging directory
        ''' </summary>
        Private m_sLogDir As String

#End Region '#Region "MEMBERS"

#Region "EVENTS"

        ''' <summary>
        ''' Raise an event to transmit a new packet
        ''' </summary>
        ''' <param name="eEndpoint"></param>
        ''' <param name="u16Type"></param>
        ''' <param name="u32Block0"></param>
        ''' <param name="u32Block1"></param>
        ''' <param name="u32Block2"></param>
        ''' <param name="u32Block3"></param>
        Public Event UserEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)
        Public Event UserEvent__SafeUDP__Tx_X3_Array(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, pu8Array() As Byte, iArrayLength As Integer)

#End Region '#Region "EVENTS"

#Region "NEW"
        ''' <summary>
        ''' New instance
        ''' </summary>
        ''' <param name="pf"></param>
        ''' <remarks></remarks>
        Public Sub New(ByRef pf As Windows.Forms.Form, ByRef pExplorer As SIL3.ApplicationSupport.ExplorerBarHelper, sLogDir As String)

            Me.m_sLogDir = sLogDir

            If sLogDir = "" Then
                MsgBox("Warning, the logging dir is blank, exiting")
                Return
            End If

            Me.m_sLogDir = Me.m_sLogDir & "FLIGHT_CONTROL\"

            'check our folder
            SIL3.FileSupport.FileHelpers.Folder__CheckWarnMake(Me.m_sLogDir)

            'setup our explorer bar
            Me.m_pExplorer = pExplorer

            Me.m_iBarIndex = Me.m_pExplorer.Bar__Add("Flight Control")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "Mission")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "SpaceX Telemetry")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "Pod Health + Fault Flags")

            Me.m_iBarIndex = Me.m_pExplorer.Bar__Add("Flight Subsystems")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "Accelerometers")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "ASI Controllers")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "Brakes")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "Stepper Motors")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "Lasers - Ccontrast")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "Lasers - OptoNCDT")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "Lasers - Distance")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "Throttle")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "Pusher")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "Geometry")


            Me.m_iBarIndex = Me.m_pExplorer.Bar__Add("Flight - Track DB")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "TrackDB - Create")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "TrackDB - Monitor")
			
            'add the panels before the bar so as we have docking working well.
            Me.m_pnlFlight__Mission = New SIL3.rLoop.rPodControl.Panels.FlightControl.Mission("Mission", Me.m_sLogDir)
            pf.Controls.Add(Me.m_pnlFlight__Mission)

            Me.m_pnlFlight__SpaceX = New SIL3.rLoop.rPodControl.Panels.FlightControl.SpaceX("SpaceX Telemetry", Me.m_sLogDir)
            pf.Controls.Add(Me.m_pnlFlight__SpaceX)

            Me.m_pnlFlight__FaultFlags = New SIL3.rLoop.rPodControl.Panels.FlightControl.Faults("Pod Health + Fault Flags", Me.m_sLogDir)
            pf.Controls.Add(Me.m_pnlFlight__FaultFlags)

            Me.m_pnlFlight__Accel = New SIL3.rLoop.rPodControl.Panels.FlightControl.Accelerometers("Accelerometers", Me.m_sLogDir)
            pf.Controls.Add(Me.m_pnlFlight__Accel)

            Me.m_pnlFlight__ASI = New SIL3.rLoop.rPodControl.Panels.FlightControl.ASI("ASI Controllers", Me.m_sLogDir)
            pf.Controls.Add(Me.m_pnlFlight__ASI)


            Me.m_pnlFlight__Contrast = New SIL3.rLoop.rPodControl.Panels.FlightControl.Contrast("Lasers - Ccontrast", Me.m_sLogDir)
            pf.Controls.Add(Me.m_pnlFlight__Contrast)

            Me.m_pnlFlight__OptoNCDT = New SIL3.rLoop.rPodControl.Panels.FlightControl.OptoNCDT("Lasers - OptoNCDT", Me.m_sLogDir)
            pf.Controls.Add(Me.m_pnlFlight__OptoNCDT)

            Me.m_pnlFlight__LaserDist = New SIL3.rLoop.rPodControl.Panels.FlightControl.LaserDistance("Lasers - Distance", Me.m_sLogDir)
            pf.Controls.Add(Me.m_pnlFlight__LaserDist)

            Me.m_pnlFlight__Brakes = New SIL3.rLoop.rPodControl.Panels.FlightControl.Brakes("Brakes", Me.m_sLogDir)
            pf.Controls.Add(Me.m_pnlFlight__Brakes)

            Me.m_pnlFlight__Stepper = New SIL3.rLoop.rPodControl.Panels.FlightControl.Stepper("Stepper Motors", Me.m_sLogDir)
            pf.Controls.Add(Me.m_pnlFlight__Stepper)

            Me.m_pnlFlight__Throttle = New SIL3.rLoop.rPodControl.Panels.FlightControl.Throttle("Throttle", Me.m_sLogDir)
            pf.Controls.Add(Me.m_pnlFlight__Throttle)

            Me.m_pnlFlight__Pusher = New SIL3.rLoop.rPodControl.Panels.FlightControl.Pusher("Pusher", Me.m_sLogDir)
            pf.Controls.Add(Me.m_pnlFlight__Pusher)
            Me.m_pnlFlight__Geometry = New SIL3.rLoop.rPodControl.Panels.FlightControl.Geometry("Geometry", Me.m_sLogDir)
            pf.Controls.Add(Me.m_pnlFlight__Geometry)


            Me.m_pnlFlight__TrackDB_Create = new SIL3.rLoop.rPodControl.Panels.FlightControl.TrackDatabase.Creator("TrackDB - Create", Me.m_sLogDir)
            pf.Controls.Add(Me.m_pnlFlight__TrackDB_Create)	
			me.m_pnlFlight__TrackDB_Monitor = new SIL3.rLoop.rPodControl.Panels.FlightControl.TrackDatabase.Monitor("TrackDB - Monitor", Me.m_sLogDir)
            pf.Controls.Add(Me.m_pnlFlight__TrackDB_Monitor)	
			
            'setup the eth
            AddHandler Me.m_pnlFlight__Mission.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlFlight__SpaceX.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlFlight__FaultFlags.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlFlight__Accel.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlFlight__ASI.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlFlight__Contrast.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlFlight__OptoNCDT.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlFlight__LaserDist.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlFlight__Brakes.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlFlight__Stepper.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlFlight__Throttle.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlFlight__Pusher.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlFlight__Geometry.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4


            AddHandler Me.m_pnlFlight__TrackDB_Create.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlFlight__TrackDB_Monitor.UserEvent__SafeUDP__Tx_X4, AddressOf Me.InternalEvent__SafeUDP__Tx_X4
            AddHandler Me.m_pnlFlight__TrackDB_Monitor.UserEvent__SafeUDP__Tx_X3_Array, AddressOf Me.InternalEvent__SafeUDP__Tx_X3_Array

            AddHandler Me.m_pExplorer.LinkClick, AddressOf Me.LinkBar_LinkClick

        End Sub

#End Region '#Region "NEW"

#Region "PANEL HELPERS"
        ''' <summary>
        ''' How or hide this panel if our text matches
        ''' </summary>
        ''' <param name="sText"></param>
        ''' <remarks></remarks>
        Public Sub Panel__HideShow(sText As String)
            Me.m_pnlFlight__Mission.Panel__HideShow(sText)
            Me.m_pnlFlight__SpaceX.Panel__HideShow(sText)
            Me.m_pnlFlight__FaultFlags.Panel__HideShow(sText)
            Me.m_pnlFlight__Accel.Panel__HideShow(sText)
            Me.m_pnlFlight__ASI.Panel__HideShow(sText)
            Me.m_pnlFlight__Contrast.Panel__HideShow(sText)
            Me.m_pnlFlight__OptoNCDT.Panel__HideShow(sText)
            Me.m_pnlFlight__LaserDist.Panel__HideShow(sText)
            Me.m_pnlFlight__Brakes.Panel__HideShow(sText)
            Me.m_pnlFlight__Stepper.Panel__HideShow(sText)
            Me.m_pnlFlight__Throttle.Panel__HideShow(sText)
            Me.m_pnlFlight__Pusher.Panel__HideShow(sText)
            Me.m_pnlFlight__Geometry.Panel__HideShow(sText)

            Me.m_pnlFlight__TrackDB_Create.Panel__HideShow(sText)
			me.m_pnlFlight__TrackDB_Monitor.Panel__HideShow(sText)
			End Sub
#End Region '#Region "PANEL HELPERS"

#Region "EXPLORER BAR"
        ''' <summary>
        ''' Called when a link is clicked
        ''' </summary>
        ''' <param name="sText"></param>
        ''' <remarks></remarks>
        Private Sub LinkBar_LinkClick(ByVal sText As String)
            Me.m_pnlFlight__Mission.Panel__HideShow(sText)
            Me.m_pnlFlight__SpaceX.Panel__HideShow(sText)
            Me.m_pnlFlight__FaultFlags.Panel__HideShow(sText)
            Me.m_pnlFlight__Accel.Panel__HideShow(sText)
            Me.m_pnlFlight__ASI.Panel__HideShow(sText)
            Me.m_pnlFlight__Contrast.Panel__HideShow(sText)
            Me.m_pnlFlight__OptoNCDT.Panel__HideShow(sText)
            Me.m_pnlFlight__LaserDist.Panel__HideShow(sText)
            Me.m_pnlFlight__Brakes.Panel__HideShow(sText)
            Me.m_pnlFlight__Stepper.Panel__HideShow(sText)
            Me.m_pnlFlight__Throttle.Panel__HideShow(sText)
            Me.m_pnlFlight__Pusher.Panel__HideShow(sText)
            Me.m_pnlFlight__Geometry.Panel__HideShow(sText)

            Me.m_pnlFlight__TrackDB_Create.Panel__HideShow(sText)
			me.m_pnlFlight__TrackDB_Monitor.Panel__HideShow(sText)
			End Sub
#End Region '#Region "EXPLORER BAR"

#Region "ETHERNET TX"

        ''' <summary>
        ''' Some lower module wants to transmit to to the eth
        ''' </summary>
        ''' <param name="eEndpoint"></param>
        ''' <param name="u16Type"></param>
        ''' <param name="u32Block0"></param>
        ''' <param name="u32Block1"></param>
        ''' <param name="u32Block2"></param>
        ''' <param name="u32Block3"></param>
        Private Sub InternalEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(eEndpoint, u16Type, u32Block0, u32Block1, u32Block2, u32Block3)
        End Sub


        Private Sub InternalEvent__SafeUDP__Tx_X3_Array(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, pu8Array() As Byte, iArrayLength As Integer)
            RaiseEvent UserEvent__SafeUDP__Tx_X3_Array(eEndpoint, u16Type, u32Block0, u32Block1, u32Block2, pu8Array, iArrayLength)
        End Sub



#End Region '#Region "ETHERNET TX"

#Region "ETHERNET RX"

        ''' <summary>
        ''' New packet in from top layer
        ''' </summary>
        ''' <param name="u16PacketType"></param>
        ''' <param name="u16PayloadLength"></param>
        ''' <param name="u8Payload"></param>
        ''' <param name="u16CRC"></param>
        ''' <param name="bCRC_OK"></param>
        ''' <param name="u32Sequence"></param>
        Public Sub InternalEvent__UDPSafe__RxPacketB(u16PacketType As UInt16, ByVal u16PayloadLength As SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As SIL3.Numerical.U16, ByVal bCRC_OK As Boolean, ByVal u32Sequence As UInt32)
            Me.m_pnlFlight__Mission.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload, u16CRC)
            Me.m_pnlFlight__FaultFlags.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload, u16CRC)


            Me.m_pnlFlight__Accel.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload, u16CRC)
            Me.m_pnlFlight__ASI.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload, u16CRC)
            Me.m_pnlFlight__Contrast.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload, u16CRC)
            Me.m_pnlFlight__OptoNCDT.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload, u16CRC)
            Me.m_pnlFlight__LaserDist.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload, u16CRC)
            Me.m_pnlFlight__Brakes.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload, u16CRC)
            Me.m_pnlFlight__Stepper.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload, u16CRC)
            Me.m_pnlFlight__Throttle.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload, u16CRC)
            Me.m_pnlFlight__Pusher.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload, u16CRC)
            Me.m_pnlFlight__Geometry.InernalEvent__UDPSafe__RxPacketB(u16PacketType, u16PayloadLength, u8Payload, u16CRC)
        End Sub

        ''' <summary>
        ''' Rx a eth packet
        ''' </summary>
        ''' <param name="u8Array"></param>
        ''' <param name="iLength"></param>
        Public Sub InternalEvent__RxPacketA(u8Array() As Byte, iLength As Integer)
            Me.m_pnlFlight__SpaceX.InternalEvent__RxPacketA(u8Array, iLength)
        End Sub


#End Region '#Region "ETHERNET RX"

    End Class

End Namespace
