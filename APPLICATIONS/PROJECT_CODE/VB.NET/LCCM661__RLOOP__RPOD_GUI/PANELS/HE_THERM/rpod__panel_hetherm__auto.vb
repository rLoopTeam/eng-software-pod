Namespace SIL3.rLoop.rPodControl.Panels.HETherm

    ''' <summary>
    ''' Automatic Temperature Control
    ''' </summary>
    ''' <remarks></remarks>
    Public Class AutoControl
	        Inherits LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"
        ''' <summary>
        ''' Total number of sensors in the system, don't touch this
        ''' </summary>
        Private Const C_NUM_TEMP_SENSORS As Integer = 24

#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        Private m_txtRxCount As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_S32
        Private m_txtFaultFlags_TOP As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags
        Private m_txtFaultFlags_Solenoid As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags
        Private m_txtFaultFlags_DS2482_0 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags
        Private m_txtFaultFlags_DS2482_1 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags
        Private m_txtFaultFlags_DS18B20 As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags

        Private m_txtNumSensors As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U8
        Private m_txtTemperature(C_NUM_TEMP_SENSORS - 1) As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32

        Private m_txtLeft_HighestIndex As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_S16
        Private m_txtRight_HighestIndex As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_S16
        Private m_txtBrake_HighestIndex As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_S16

        Private m_txtLeft_HighestVal As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtRight_HighestVal As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtBrake_HighestVal As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32

        Private m_txtLeft_AvgVal As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtRight_AvgVal As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtBrake_AvgVal As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32

        Private m_txtLeft_CoolingState As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtRight_CoolingState As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtBrake_CoolingState As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper


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

            Dim l0 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper(10, 10, "Rx Count", Me.m_pInnerPanel)
            Me.m_txtRxCount = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_S32(100, l0)

            Dim l1 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Module Flags")
            l1.Layout__AboveRightControl(l0, Me.m_txtRxCount)
            Me.m_txtFaultFlags_TOP = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l1)
            'Me.m_txtFaultFlags_TOP.FlagsFile__Read("../../../../FIRMWARE/PROJECT_CODE/LCCM721__RLOOP__HE_THERM/he_therm__fault_flags.h", "CORE")

            Dim l2 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Solenoid Faults")
            l2.Layout__AboveRightControl(l1, Me.m_txtFaultFlags_TOP)
            Me.m_txtFaultFlags_Solenoid = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l2)

            Dim l3 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("DS2482:0 Faults")
            l3.Layout__AboveRightControl(l2, Me.m_txtFaultFlags_Solenoid)
            Me.m_txtFaultFlags_DS2482_0 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l3)
            Me.m_txtFaultFlags_DS2482_0.FlagsFile__Read("../../../../FIRMWARE/COMMON_CODE/MULTICORE/LCCM641__MULTICORE__DS2482S/ds2482s__fault_flags.h", "CORE")

            Dim l4 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("DS2482:1 Faults")
            l4.Layout__AboveRightControl(l3, Me.m_txtFaultFlags_DS2482_0)
            Me.m_txtFaultFlags_DS2482_1 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l4)
            Me.m_txtFaultFlags_DS2482_1.FlagsFile__Read("../../../../FIRMWARE/COMMON_CODE/MULTICORE/LCCM641__MULTICORE__DS2482S/ds2482s__fault_flags.h", "CORE")

            Dim l5 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("DS18B20 Faults")
            l5.Layout__AboveRightControl(l3, Me.m_txtFaultFlags_DS2482_1)
            Me.m_txtFaultFlags_DS18B20 = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l5)
            'Me.m_txtFaultFlags_DS18B20_1.FlagsFile__Read("../../../../FIRMWARE/COMMON_CODE/MULTICORE/LCCM641__MULTICORE__DS2482S/ds2482s__fault_flags.h", "CORE")

            Dim l6 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Found Sensors")
            l6.Layout__BelowControl(Me.m_txtRxCount)
            Me.m_txtNumSensors = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U8(100, l6)

            'do the rows of sensors
            Dim iIndex As Integer = 0
            Dim l7(C_NUM_TEMP_SENSORS - 1) As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper
            For iCounter As Integer = 0 To C_NUM_TEMP_SENSORS - 1
                l7(iIndex) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("T" & iIndex.ToString("00") & " °C")
                If iIndex = 0 Then
                    l7(iIndex).Layout__BelowControl(Me.m_txtNumSensors)
                ElseIf iIndex = 8 Then
                    l7(iIndex).Layout__BelowControl(Me.m_txtTemperature(iIndex - 8))
                ElseIf iIndex = 16 Then
                    l7(iIndex).Layout__BelowControl(Me.m_txtTemperature(iIndex - 8))
                ElseIf iIndex = 24 Then
                    l7(iIndex).Layout__BelowControl(Me.m_txtTemperature(iIndex - 8))
                Else
                    l7(iIndex).Layout__AboveRightControl(l7(iIndex - 1), Me.m_txtTemperature(iIndex - 1))
                End If
                Me.m_txtTemperature(iIndex) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(100, l7(iIndex))
                iIndex += 1
            Next

            Dim l80 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("L High Idx", Me.m_txtTemperature(16))
            Me.m_txtLeft_HighestIndex = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_S16(100, l80)
            Dim l81 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("L High °C")
            l81.Layout__AboveRightControl(l80, Me.m_txtLeft_HighestIndex)
            Me.m_txtLeft_HighestVal = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(100, l81)
            Dim l82 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("L Average °C")
            l82.Layout__AboveRightControl(l81, Me.m_txtLeft_HighestVal)
            Me.m_txtLeft_AvgVal = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(100, l82)
            Dim l83 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Cooling State")
            l83.Layout__AboveRightControl(l82, Me.m_txtLeft_AvgVal)
            Me.m_txtLeft_CoolingState = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper(100, l83)


            Dim l90 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("R High Idx", Me.m_txtLeft_HighestIndex)
            Me.m_txtRight_HighestIndex = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_S16(100, l90)
            Dim l91 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("R High °C")
            l91.Layout__AboveRightControl(l90, Me.m_txtRight_HighestIndex)
            Me.m_txtRight_HighestVal = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(100, l91)
            Dim l92 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("R Average °C")
            l92.Layout__AboveRightControl(l91, Me.m_txtRight_HighestVal)
            Me.m_txtRight_AvgVal = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(100, l92)
            Dim l93 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Cooling State")
            l93.Layout__AboveRightControl(l92, Me.m_txtRight_AvgVal)
            Me.m_txtRight_CoolingState = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper(100, l93)


            Dim lA0 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Brake High Idx", Me.m_txtRight_HighestIndex)
            Me.m_txtBrake_HighestIndex = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_S16(100, lA0)
            Dim lA1 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Brake High °C")
            lA1.Layout__AboveRightControl(lA0, Me.m_txtBrake_HighestIndex)
            Me.m_txtBrake_HighestVal = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(100, lA1)
            Dim lA2 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Brake Average °C")
            lA2.Layout__AboveRightControl(lA1, Me.m_txtBrake_HighestVal)
            Me.m_txtBrake_AvgVal = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(100, lA2)
            Dim lA3 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Cooling State")
            lA3.Layout__AboveRightControl(lA2, Me.m_txtBrake_AvgVal)
            Me.m_txtBrake_CoolingState = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper(100, lA3)


        End Sub
#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON"

        Private Sub btnSolOpen_0(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__HETHERM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__HET__MANUAL_CONTROL,
                                                 &HAA117788L,
                                                 0, 1, 0)

        End Sub

        Private Sub btnSolClose_0(sender As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__HETHERM,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__HET__MANUAL_CONTROL,
                                                 &HAA117788L,
                                                 0, 0, 0)

        End Sub




#End Region '#Region "BUTTON"

#Region "ETH RX"
        ''' <summary>
        ''' New Packet In
        ''' </summary>
        ''' <param name="ePacketType"></param>
        ''' <param name="u16PayloadLength"></param>
        ''' <param name="u8Payload"></param>
        Public Sub InernalEvent__UDPSafe__RxPacketB(ByVal ePacketType As SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T, ByVal u16PayloadLength As LAPP188__RLOOP__LIB.SIL3.Numerical.U16, ByRef u8Payload() As Byte)

            'only do if we have been created
            If MyBase.m_bLayout = True Then

                'match thepacket
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__HET__SEND_THERM_PACKET Then

                    Dim iOffset As Integer = 0

                    iOffset += Me.m_txtFaultFlags_TOP.Flags__Update(u8Payload, iOffset, True)
                    iOffset += Me.m_txtFaultFlags_Solenoid.Flags__Update(u8Payload, iOffset, True)
                    iOffset += Me.m_txtFaultFlags_DS2482_0.Flags__Update(u8Payload, iOffset, True)
                    iOffset += Me.m_txtFaultFlags_DS2482_1.Flags__Update(u8Payload, iOffset, True)
                    iOffset += Me.m_txtFaultFlags_DS18B20.Flags__Update(u8Payload, iOffset, True)
                    iOffset += Me.m_txtNumSensors.Value__Update(u8Payload, iOffset)

                    'sensors
                    For iCounter As Integer = 0 To C_NUM_TEMP_SENSORS - 1
                        iOffset += Me.m_txtTemperature(iCounter).Value__Update(u8Payload, iOffset)

                        'RomID
                        iOffset += 8
                    Next

                    iOffset += Me.m_txtLeft_HighestIndex.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtRight_HighestIndex.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtBrake_HighestIndex.Value__Update(u8Payload, iOffset)

                    iOffset += Me.m_txtLeft_HighestVal.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtRight_HighestVal.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtBrake_HighestVal.Value__Update(u8Payload, iOffset)

                    iOffset += Me.m_txtLeft_AvgVal.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtRight_AvgVal.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtBrake_AvgVal.Value__Update(u8Payload, iOffset)

                    Select Case u8Payload(iOffset)
                        Case &H0
                            Me.m_txtLeft_CoolingState.Threadsafe__SetText("OFF")
                        Case &H1
                            Me.m_txtLeft_CoolingState.Threadsafe__SetText("WARN")
                        Case &H2
                            Me.m_txtLeft_CoolingState.Threadsafe__SetText("CRITICAL")
                        Case Else
                            Me.m_txtLeft_CoolingState.Threadsafe__SetText("ERROR?")
                    End Select
                    iOffset += 1

                    Select Case u8Payload(iOffset)
                        Case &H0
                            Me.m_txtRight_CoolingState.Threadsafe__SetText("OFF")
                        Case &H1
                            Me.m_txtRight_CoolingState.Threadsafe__SetText("WARN")
                        Case &H2
                            Me.m_txtRight_CoolingState.Threadsafe__SetText("CRITICAL")
                        Case Else
                            Me.m_txtRight_CoolingState.Threadsafe__SetText("ERROR?")
                    End Select
                    iOffset += 1

                    Select Case u8Payload(iOffset)
                        Case &H0
                            Me.m_txtBrake_CoolingState.Threadsafe__SetText("OFF")
                        Case &H1
                            Me.m_txtBrake_CoolingState.Threadsafe__SetText("WARN")
                        Case &H2
                            Me.m_txtBrake_CoolingState.Threadsafe__SetText("CRITICAL")
                        Case Else
                            Me.m_txtBrake_CoolingState.Threadsafe__SetText("ERROR?")
                    End Select
                    iOffset += 1

                    Me.m_iRxCount += 1
                    Me.m_txtRxCount.Threadsafe__SetText(Me.m_iRxCount.ToString)


                End If
            End If

        End Sub

#End Region '#Region "ETH RX"

    End Class


End Namespace
