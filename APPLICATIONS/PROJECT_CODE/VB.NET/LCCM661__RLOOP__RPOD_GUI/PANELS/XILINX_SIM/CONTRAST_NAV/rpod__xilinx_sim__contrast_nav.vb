Namespace SIL3.rLoop.rPodControl.Panels.XilinxSim

    ''' <summary>
    ''' Contrast Navigation System
    ''' </summary>
    ''' <remarks></remarks>
    Public Class ContrastNav
        Inherits SIL3.ApplicationSupport.PanelTemplate


#Region "MEMBERS"

        ''' <summary>
        ''' Count of Rx Packets
        ''' </summary>
        Private m_iRxCount As Integer

        ''' <summary>
        ''' Count of Packets
        ''' </summary>
        Private m_txtCount As SIL3.ApplicationSupport.TextBoxHelper

        ''' <summary>
        ''' The simulation status
        ''' </summary>
        Private m_txtStatus As SIL3.ApplicationSupport.TextBoxHelper

        ''' <summary>
        ''' Simulation G-Force
        ''' </summary>
        Private m_txtGForce As SIL3.ApplicationSupport.TextBoxHelper

        ''' <summary>
        ''' Last Rx CRC
        ''' </summary>
        Private m_txtCRC As SIL3.ApplicationSupport.TextBoxHelper

#End Region '#Region "MEMBERS"

#Region "NEW"
        ''' <summary>
        ''' New instance
        ''' </summary>
        ''' <param name="sPanelText"></param>
        ''' <remarks></remarks>
        Public Sub New(sPanelText As String)
            MyBase.New(sPanelText)


        End Sub
#End Region '#Region "NEW"

#Region "EVENTS"

        ''' <summary>
        ''' Raised wehen we want to transmit a control packet
        ''' </summary>
        ''' <param name="u16Type"></param>
        ''' <param name="u32Block0"></param>
        ''' <param name="u32Block1"></param>
        ''' <param name="u32Block2"></param>
        ''' <param name="u32Block3"></param>
        ''' <remarks></remarks>
        Public Event UserEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)

        ''' <summary>
        ''' New Packet In
        ''' </summary>
        ''' <param name="ePacketType"></param>
        ''' <param name="u16PayloadLength"></param>
        ''' <param name="u8Payload"></param>
        ''' <param name="u16CRC"></param>
        Public Sub InernalEvent__UDPSafe__RxPacketB(ByVal ePacketType As SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T, ByVal u16PayloadLength As SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As SIL3.Numerical.U16)

            'only do if we have been created
            If MyBase.m_bLayout = True Then

                'check for our sim packet type
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__XILINX_SIM__TX_PROGRESS_UPDATE Then

                    Dim iOffset As Integer = 0
                    Dim pU32Status As New SIL3.Numerical.U32(u8Payload, iOffset)
                    iOffset += 4

                    Dim u8Status As New SIL3.Numerical.U8(u8Payload, iOffset)
                    iOffset += 1

                    Me.m_txtStatus.Threadsafe__SetText(u8Status.To_String)

                    Me.m_iRxCount += 1
                    Me.m_txtCount.Threadsafe__SetText(Me.m_iRxCount.ToString)


                End If
            End If

        End Sub


#End Region '#Region "EVENTS"

#Region "PANEL LAYOUT"
        ''' <summary>
        ''' Create our layout prior to being shown
        ''' </summary>
        ''' <remarks></remarks>
        Public Overrides Sub LayoutPanel()


            Dim la0 As New SIL3.ApplicationSupport.LabelHelper(10, 10, "Simulation G-Force", MyBase.m_pInnerPanel)
            Me.m_txtGForce = New SIL3.ApplicationSupport.TextBoxHelper(100, la0)
            Me.m_txtGForce.Threadsafe__SetText("2.0")


            Dim la01 As New SIL3.ApplicationSupport.LabelHelper("Track Simulation Run", Me.m_txtGForce)
            Dim btnStartRun As New SIL3.ApplicationSupport.ButtonHelper(100, "Start Run", AddressOf Me.btnStartRun__Click)
            btnStartRun.Layout__BelowControl(la01)
            Dim btnStopRun As New SIL3.ApplicationSupport.ButtonHelper(100, "Stop Run", AddressOf Me.btnStopRun__Click)
            btnStopRun.Layout__RightOfControl(btnStartRun)

            Dim la1 As New SIL3.ApplicationSupport.LabelHelper("Manual Laser Control", btnStartRun)
            Dim btnL0_On As New SIL3.ApplicationSupport.ButtonHelper(100, "Laser0 On", AddressOf Me.btnLaser0_On__Click)
            btnL0_On.Layout__BelowControl(la1)
            Dim btnL0_Off As New SIL3.ApplicationSupport.ButtonHelper(100, "Laser0 Off", AddressOf Me.btnLaser0_Off__Click)
            btnL0_Off.Layout__RightOfControl(btnL0_On)

            Dim btnL1_On As New SIL3.ApplicationSupport.ButtonHelper(100, "Laser1 On", AddressOf Me.btnLaser1_On__Click)
            btnL1_On.Layout__BelowControl(btnL0_On)
            Dim btnL1_Off As New SIL3.ApplicationSupport.ButtonHelper(100, "Laser1 Off", AddressOf Me.btnLaser1_Off__Click)
            btnL1_Off.Layout__RightOfControl(btnL1_On)

            Dim btnL2_On As New SIL3.ApplicationSupport.ButtonHelper(100, "Laser2 On", AddressOf Me.btnLaser2_On__Click)
            btnL2_On.Layout__BelowControl(btnL1_On)
            Dim btnL2_Off As New SIL3.ApplicationSupport.ButtonHelper(100, "Laser2 Off", AddressOf Me.btnLaser2_Off__Click)
            btnL2_Off.Layout__RightOfControl(btnL2_On)

            Dim l10 As New SIL3.ApplicationSupport.LabelHelper("Status")
            l10.Layout__BelowControl(btnL2_On)
            Me.m_txtStatus = New SIL3.ApplicationSupport.TextBoxHelper(100, l10)

            Dim l11 As New SIL3.ApplicationSupport.LabelHelper("Rx Count")
            l11.Layout__BelowControl(m_txtStatus)
            Me.m_txtCount = New SIL3.ApplicationSupport.TextBoxHelper(100, l11)


        End Sub
#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        Private Sub btnStartRun__Click(s As Object, e As EventArgs)

            Dim pF32 As New SIL3.Numerical.F32(CSng(Me.m_txtGForce.Text))

            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__XILINX_SIM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__XILINX_SIM__SIMULATION_CONTROL,
                                                 1, pF32.Union__Uint32, 0, 0)
        End Sub
        Private Sub btnStopRun__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__XILINX_SIM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__XILINX_SIM__SIMULATION_CONTROL,
                                                 0, 0, 0, 0)
        End Sub
        Private Sub btnLaser0_On__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__XILINX_SIM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__XILINX_SIM__MANUAL_LASER_CONTROL,
                                                 0, 1, 0, 0)
        End Sub
        Private Sub btnLaser0_Off__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__XILINX_SIM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__XILINX_SIM__MANUAL_LASER_CONTROL,
                                                 0, 0, 0, 0)
        End Sub
        Private Sub btnLaser1_On__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__XILINX_SIM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__XILINX_SIM__MANUAL_LASER_CONTROL,
                                                 1, 1, 0, 0)
        End Sub
        Private Sub btnLaser1_Off__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__XILINX_SIM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__XILINX_SIM__MANUAL_LASER_CONTROL,
                                                 1, 0, 0, 0)
        End Sub
        Private Sub btnLaser2_On__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__XILINX_SIM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__XILINX_SIM__MANUAL_LASER_CONTROL,
                                                 2, 1, 0, 0)
        End Sub
        Private Sub btnLaser2_Off__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__XILINX_SIM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__XILINX_SIM__MANUAL_LASER_CONTROL,
                                                 2, 0, 0, 0)
        End Sub



#End Region '#Region "BUTTON HELPERS"

    End Class


End Namespace
