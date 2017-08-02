Namespace SIL3.rLoop.rPodControl.Panels.LandingGear

    ''' <summary>
    ''' Manual Landing Gear Control
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Manual
        Inherits LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.PanelTemplate

#Region "MEMBERS"

        Private m_trkSpeedA0 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TrackBarHelper
        Private m_trkSpeedA1 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TrackBarHelper
        Private m_trkSpeedA2 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TrackBarHelper
        Private m_trkSpeedA3 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TrackBarHelper


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

            Dim lA0 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper(10, 10, "Actuator 0", Me.m_pInnerPanel)
            Dim btnA0_Stop As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Stop", AddressOf Me.btnA0_Stop)
            btnA0_Stop.Layout__BelowControl(lA0)
            Dim btnA0_Extend As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Extend", AddressOf Me.btnA0_Extend)
            btnA0_Extend.Layout__RightOfControl(btnA0_Stop)
            Dim btnA0_Retract As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Retract", AddressOf Me.btnA0_Retract)
            btnA0_Retract.Layout__RightOfControl(btnA0_Extend)

            Me.m_trkSpeedA0 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TrackBarHelper()
            Me.m_trkSpeedA0.Layout__RightOfControl(btnA0_Retract)
            With Me.m_trkSpeedA0
                .Size = New Size(250, 24)
                .Minimum = 0
                .Maximum = 100
                .TickFrequency = 10
                .Value = 80
                .TickStyle = TickStyle.BottomRight
            End With

            Dim lA1 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Actuator 1", btnA0_Stop)
            Dim btnA1_Stop As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Stop", AddressOf Me.btnA1_Stop)
            btnA1_Stop.Layout__BelowControl(lA1)
            Dim btnA1_Extend As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Extend", AddressOf Me.btnA1_Extend)
            btnA1_Extend.Layout__RightOfControl(btnA1_Stop)
            Dim btnA1_Retract As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Retract", AddressOf Me.btnA1_Retract)
            btnA1_Retract.Layout__RightOfControl(btnA1_Extend)

            Me.m_trkSpeedA1 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TrackBarHelper()
            Me.m_trkSpeedA1.Layout__RightOfControl(btnA1_Retract)
            With Me.m_trkSpeedA1
                .Size = New Size(250, 24)
                .Minimum = 0
                .Maximum = 100
                .TickFrequency = 10
                .Value = 80
                .TickStyle = TickStyle.BottomRight
            End With

            Dim lA2 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Actuator 2", btnA1_Stop)
            Dim btnA2_Stop As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Stop", AddressOf Me.btnA2_Stop)
            btnA2_Stop.Layout__BelowControl(lA2)
            Dim btnA2_Extend As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Extend", AddressOf Me.btnA2_Extend)
            btnA2_Extend.Layout__RightOfControl(btnA2_Stop)
            Dim btnA2_Retract As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Retract", AddressOf Me.btnA2_Retract)
            btnA2_Retract.Layout__RightOfControl(btnA2_Extend)

            Me.m_trkSpeedA2 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TrackBarHelper()
            Me.m_trkSpeedA2.Layout__RightOfControl(btnA2_Retract)
            With Me.m_trkSpeedA2
                .Size = New Size(250, 24)
                .Minimum = 0
                .Maximum = 100
                .TickFrequency = 10
                .Value = 80
                .TickStyle = TickStyle.BottomRight
            End With

            Dim lA3 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Actuator 3", btnA2_Stop)
            Dim btnA3_Stop As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Stop", AddressOf Me.btnA3_Stop)
            btnA3_Stop.Layout__BelowControl(lA3)
            Dim btnA3_Extend As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Extend", AddressOf Me.btnA3_Extend)
            btnA3_Extend.Layout__RightOfControl(btnA3_Stop)
            Dim btnA3_Retract As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Retract", AddressOf Me.btnA3_Retract)
            btnA3_Retract.Layout__RightOfControl(btnA3_Extend)

            Me.m_trkSpeedA3 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TrackBarHelper()
            Me.m_trkSpeedA3.Layout__RightOfControl(btnA3_Retract)
            With Me.m_trkSpeedA3
                .Size = New Size(250, 24)
                .Minimum = 0
                .Maximum = 100
                .TickFrequency = 10
                .Value = 80
                .TickStyle = TickStyle.BottomRight
            End With

        End Sub
#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON"

        Private Sub btnA0_Stop(sender As Object, e As EventArgs)
            Dim u32Index As UInt32 = 0
            Dim f32Speed As New LAPP188__RLOOP__LIB.SIL3.Numerical.F32(CSng(Me.m_trkSpeedA0.Value / 100))
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__MANUAL_MODE,
                                                 &HABAB1122L,
                                                 u32Index, 0, f32Speed.Union__Uint32)

        End Sub

        Private Sub btnA0_Retract(sender As Object, e As EventArgs)
            Dim u32Index As UInt32 = 0
            Dim f32Speed As New LAPP188__RLOOP__LIB.SIL3.Numerical.F32(CSng(Me.m_trkSpeedA0.Value / 100))
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__MANUAL_MODE,
                                                 &HABAB1122L,
                                                 u32Index, 1, f32Speed.Union__Uint32)
        End Sub

        Private Sub btnA0_Extend(sender As Object, e As EventArgs)
            Dim u32Index As UInt32 = 0
            Dim f32Speed As New LAPP188__RLOOP__LIB.SIL3.Numerical.F32(CSng(Me.m_trkSpeedA0.Value / 100))
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__MANUAL_MODE,
                                                 &HABAB1122L,
                                                 u32Index, 2, f32Speed.Union__Uint32)

        End Sub


        Private Sub btnA1_Stop(sender As Object, e As EventArgs)
            Dim u32Index As UInt32 = 1
            Dim f32Speed As New LAPP188__RLOOP__LIB.SIL3.Numerical.F32(CSng(Me.m_trkSpeedA1.Value / 100))
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__MANUAL_MODE,
                                                 &HABAB1122L,
                                                 u32Index, 0, f32Speed.Union__Uint32)

        End Sub

        Private Sub btnA1_Retract(sender As Object, e As EventArgs)
            Dim u32Index As UInt32 = 1
            Dim f32Speed As New LAPP188__RLOOP__LIB.SIL3.Numerical.F32(CSng(Me.m_trkSpeedA1.Value / 100))
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__MANUAL_MODE,
                                                 &HABAB1122L,
                                                 u32Index, 1, f32Speed.Union__Uint32)
        End Sub

        Private Sub btnA1_Extend(sender As Object, e As EventArgs)
            Dim u32Index As UInt32 = 1
            Dim f32Speed As New LAPP188__RLOOP__LIB.SIL3.Numerical.F32(CSng(Me.m_trkSpeedA1.Value / 100))
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__MANUAL_MODE,
                                                 &HABAB1122L,
                                                 u32Index, 2, f32Speed.Union__Uint32)

        End Sub

        Private Sub btnA2_Stop(sender As Object, e As EventArgs)
            Dim u32Index As UInt32 = 2
            Dim f32Speed As New LAPP188__RLOOP__LIB.SIL3.Numerical.F32(CSng(Me.m_trkSpeedA2.Value / 100))
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__MANUAL_MODE,
                                                 &HABAB1122L,
                                                 u32Index, 0, f32Speed.Union__Uint32)

        End Sub

        Private Sub btnA2_Retract(sender As Object, e As EventArgs)
            Dim u32Index As UInt32 = 2
            Dim f32Speed As New LAPP188__RLOOP__LIB.SIL3.Numerical.F32(CSng(Me.m_trkSpeedA2.Value / 100))
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__MANUAL_MODE,
                                                 &HABAB1122L,
                                                 u32Index, 1, f32Speed.Union__Uint32)
        End Sub

        Private Sub btnA2_Extend(sender As Object, e As EventArgs)
            Dim u32Index As UInt32 = 2
            Dim f32Speed As New LAPP188__RLOOP__LIB.SIL3.Numerical.F32(CSng(Me.m_trkSpeedA2.Value / 100))
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__MANUAL_MODE,
                                                 &HABAB1122L,
                                                 u32Index, 2, f32Speed.Union__Uint32)

        End Sub

        Private Sub btnA3_Stop(sender As Object, e As EventArgs)
            Dim u32Index As UInt32 = 3
            Dim f32Speed As New LAPP188__RLOOP__LIB.SIL3.Numerical.F32(CSng(Me.m_trkSpeedA3.Value / 100))
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__MANUAL_MODE,
                                                 &HABAB1122L,
                                                 u32Index, 0, f32Speed.Union__Uint32)

        End Sub

        Private Sub btnA3_Retract(sender As Object, e As EventArgs)
            Dim u32Index As UInt32 = 3
            Dim f32Speed As New LAPP188__RLOOP__LIB.SIL3.Numerical.F32(CSng(Me.m_trkSpeedA3.Value / 100))
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__MANUAL_MODE,
                                                 &HABAB1122L,
                                                 u32Index, 1, f32Speed.Union__Uint32)
        End Sub

        Private Sub btnA3_Extend(sender As Object, e As EventArgs)
            Dim u32Index As UInt32 = 3
            Dim f32Speed As New LAPP188__RLOOP__LIB.SIL3.Numerical.F32(CSng(Me.m_trkSpeedA3.Value / 100))
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__LGU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__MANUAL_MODE,
                                                 &HABAB1122L,
                                                 u32Index, 2, f32Speed.Union__Uint32)

        End Sub

#End Region '#Region "BUTTON"

#Region "ETHERNET"
        ''' <summary>
        ''' New Packet In
        ''' </summary>
        ''' <param name="ePacketType"></param>
        ''' <param name="u16PayloadLength"></param>
        ''' <param name="u8Payload"></param>
        ''' <param name="u16CRC"></param>
        Public Sub InernalEvent__UDPSafe__RxPacketB(ByVal ePacketType As SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T, ByVal u16PayloadLength As LAPP188__RLOOP__LIB.SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As LAPP188__RLOOP__LIB.SIL3.Numerical.U16)

            'only do if we have been created
            If MyBase.m_bLayout = True Then

                'check for our sim packet type
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LGU__TX_STATUS_PACKET Then

                    Dim iOffset As Integer = 0

                    'iOffset += Me.m_txtFaultFlags.Flags__Update(u8Payload, iOffset, True)

                    'For iCounter As Integer = 0 To C_NUM_ACTUATORS - 1
                    '    iOffset += Me.m_txtA_Flags(iCounter).Flags__Update(u8Payload, iOffset, True)
                    '    iOffset += Me.m_txtA_ADCRaw(iCounter).Value__Update(u8Payload, iOffset)
                    '    iOffset += Me.m_txtA_Extension(iCounter).Value__Update(u8Payload, iOffset)
                    '    iOffset += Me.m_txtA_ComputedHeight(iCounter).Value__Update(u8Payload, iOffset)
                    '    iOffset += Me.m_txtA_ExtendLimit(iCounter).Value__Update(u8Payload, iOffset)
                    '    iOffset += Me.m_txtA_RetractLimit(iCounter).Value__Update(u8Payload, iOffset)

                    '    'spares
                    '    iOffset += 16
                    'Next

                End If
            End If

        End Sub

#End Region '#Region "ETHERNET"

    End Class


End Namespace
