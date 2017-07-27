Namespace SIL3.rLoop.rPodControl.Panels.AuxProp

    ''' <summary>
    ''' Manual AuxProp Control
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Manual
	        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "MEMBERS"

        Private m_pbSpeed As New SIL3.ApplicationSupport.TrackBarHelper
        Private m_txtFaultFlags As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtRxCount As SIL3.ApplicationSupport.TextBoxHelper_S32
        Private m_iRxCount As Integer
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
        Public Event UserEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)

#End Region '#Region "EVENTS"

#Region "PANEL LAYOUT"
        ''' <summary>
        ''' Create our layout prior to being shown
        ''' </summary>
        ''' <remarks></remarks>
        Public Overrides Sub LayoutPanel()

            Dim l1 As New SIL3.ApplicationSupport.LabelHelper(10, 10, "Fault Flags", Me.m_pInnerPanel)
            Me.m_txtFaultFlags = New SIL3.ApplicationSupport.TextBoxHelper(100, l1)

            Dim l1a As New SIL3.ApplicationSupport.LabelHelper("Rx Packets")
            l1a.Layout__AboveRightControl(l1, Me.m_txtFaultFlags)
            Me.m_txtRxCount = New SIL3.ApplicationSupport.TextBoxHelper_S32(100, l1a)


            Dim l2a As New SIL3.ApplicationSupport.LabelHelper("Clutches", Me.m_txtFaultFlags)
            Dim btnClutch_Disengage As New SIL3.ApplicationSupport.ButtonHelper(100, "Disengage", AddressOf Me.btnClutches_Disengage)
            btnClutch_Disengage.Layout__BelowControl(l2a)
            Dim btnClutch_Engage As New SIL3.ApplicationSupport.ButtonHelper(100, "Engage", AddressOf Me.btnClutches_Engage)
            btnClutch_Engage.Layout__RightOfControl(btnClutch_Disengage)


            Dim l20a As New SIL3.ApplicationSupport.LabelHelper("Motor Enable", btnClutch_Disengage)
            Dim btnMotor_Enable As New SIL3.ApplicationSupport.ButtonHelper(100, "Enable", AddressOf Me.btnMotor_Enable)
            btnMotor_Enable.Layout__BelowControl(l20a)
            Dim btnMotor_Disable As New SIL3.ApplicationSupport.ButtonHelper(100, "Disable", AddressOf Me.btnMotor_Disable)
            btnMotor_Disable.Layout__RightOfControl(btnMotor_Enable)


            Dim l3a As New SIL3.ApplicationSupport.LabelHelper("Directon Control", btnMotor_Enable)
            Dim btnMotor_DirR As New SIL3.ApplicationSupport.ButtonHelper(100, "Reverse", AddressOf Me.btnMotor_Reverse)
            btnMotor_DirR.Layout__BelowControl(l3a)
            Dim btnMotor_DirF As New SIL3.ApplicationSupport.ButtonHelper(100, "Forward", AddressOf Me.btnMotor_Forward)
            btnMotor_DirF.Layout__RightOfControl(btnMotor_DirR)

            Dim l4 As New SIL3.ApplicationSupport.LabelHelper("Velocity (mm/s)", btnMotor_DirR)

            Me.m_pbSpeed = New SIL3.ApplicationSupport.TrackBarHelper
            Me.m_pbSpeed.Layout__BelowControl(l4)
            Me.m_pbSpeed.Size = New Size(250, 24)
            Me.m_pbSpeed.Minimum = 0
            Me.m_pbSpeed.Maximum = 1000
            Me.m_pbSpeed.TickFrequency = 100
            Me.m_pbSpeed.TickStyle = TickStyle.BottomRight

            Dim btnApply As New SIL3.ApplicationSupport.ButtonHelper(100, "Apply", AddressOf Me.btnApply_Velocity, Me.m_pbSpeed)


        End Sub
#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON"

        Private Sub btnApply_Velocity(sender As Object, e As EventArgs)

            Dim u32Val As UInt32 = UInt32.Parse(CInt(Me.m_pbSpeed.Value))

            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU_MOTOR__SPEED_MANUAL,
                                                 &H11223399L,
                                                 u32Val, 0, 0)


        End Sub

        Private Sub btnClutches_Disengage(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU_CLUTCH__MANUAL,
                                                 &H11223344L,
                                                 0, 0, 0)

        End Sub

        Private Sub btnClutches_Engage(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU_CLUTCH__MANUAL,
                                                 &H11223344L,
                                                 0, 1, 0)

        End Sub

        Private Sub btnMotor_Disable(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU_MOTOR__ENABLE_MANUAL,
                                                 &H11223377L,
                                                0, 0, 0)

        End Sub

        Private Sub btnMotor_Enable(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU_MOTOR__ENABLE_MANUAL,
                                                 &H11223377L,
                                                 0, 1, 0)

        End Sub



        Private Sub btnMotor_Reverse(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU_MOTOR__DIRECTION_MANUAL,
                                                 &H11223388L,
                                                 0, 0, 0)

        End Sub

        Private Sub btnMotor_Forward(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__APU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU_MOTOR__DIRECTION_MANUAL,
                                                 &H11223388L,
                                                0, 1, 0)
        End Sub





#End Region '#Region "BUTTON"

#Region "ETH RX"
        ''' <summary>
        ''' New Packet In
        ''' </summary>
        ''' <param name="ePacketType"></param>
        ''' <param name="u16PayloadLength"></param>
        ''' <param name="u8Payload"></param>
        Public Sub InernalEvent__UDPSafe__RxPacketB(ByVal ePacketType As SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T, ByVal u16PayloadLength As SIL3.Numerical.U16, ByRef u8Payload() As Byte)

            'only do if we have been created
            If MyBase.m_bLayout = True Then

                'match thepacket
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__APU__STATUS_PACKET Then

                    Dim iOffset As Integer = 0

                    iOffset += 4 'Me.m_txtFaultFlags_TOP.Flags__Update(u8Payload, iOffset, True)

                    Me.m_iRxCount += 1
                    Me.m_txtRxCount.Threadsafe__SetText(Me.m_iRxCount.ToString)


                End If
            End If

        End Sub

#End Region '#Region "ETH RX"


    End Class


End Namespace
