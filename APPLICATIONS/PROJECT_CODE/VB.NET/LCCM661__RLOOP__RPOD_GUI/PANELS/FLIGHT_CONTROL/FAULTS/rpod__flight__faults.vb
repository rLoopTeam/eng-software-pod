Namespace SIL3.rLoop.rPodControl.Panels.FlightControl

    ''' <summary>
    ''' All fault Flags
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Faults
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"
        Private Const C_NUM__FAULT_FLAGS As Integer = 23 + 8 + 6
#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        Private m_iRxCount As Integer
        Private m_txtRxCount As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtFaults(C_NUM__FAULT_FLAGS - 1) As SIL3.ApplicationSupport.TextBoxHelper_FaultFlags

        ''' <summary>
        ''' The logging directory
        ''' </summary>
        Private m_sLogDir As String

#End Region '#Region "MEMBERS"

#Region "NEW"
        ''' <summary>
        ''' New instance
        ''' </summary>
        ''' <param name="sPanelText"></param>
        ''' <remarks></remarks>
        Public Sub New(sPanelText As String, sLog As String)
            MyBase.New(sPanelText)

            Me.m_sLogDir = sLog
            Me.m_sLogDir = Me.m_sLogDir & "FAULTS\"

            'check our folder
            SIL3.FileSupport.FileHelpers.Folder__CheckWarnMake(Me.m_sLogDir)

        End Sub
#End Region '#Region "New"

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

                'check for our faults packet
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__TX_ALL_FAULT_FLAGS Then

                    Dim iOffset As Integer = 0

                    Dim pu32Flags(C_NUM__FAULT_FLAGS - 1) As SIL3.Numerical.U32

                    For iCounter As Integer = 0 To C_NUM__FAULT_FLAGS - 1
                        pu32Flags(iCounter) = New SIL3.Numerical.U32(u8Payload, iOffset)
                        iOffset += 4
                        Me.m_txtFaults(iCounter).Flags__Update(pu32Flags(iCounter), True)
                    Next


                    Me.m_iRxCount += 1
                    Me.m_txtRxCount.Threadsafe__SetText(Me.m_iRxCount.ToString)



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

            Dim l0(C_NUM__FAULT_FLAGS - 1) As SIL3.ApplicationSupport.LabelHelper
            Dim iIndex As Integer = 0

            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper(10, 10, "General Faults", MyBase.m_pInnerPanel)
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            Me.m_txtFaults(iIndex).Flags__Add("This is Line 1")
            Me.m_txtFaults(iIndex).Flags__Add("This is Line 2")

            iIndex += 1

            Dim l11 As New SIL3.ApplicationSupport.LabelHelper("Rx Count")
            l11.Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
            Me.m_txtRxCount = New SIL3.ApplicationSupport.TextBoxHelper(100, l11)

            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("Accel: Faults")
            l0(iIndex).Layout__BelowControl(Me.m_txtFaults(iIndex - 1))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1

            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("MMA8451:0 Faults")
            l0(iIndex).Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1

            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("MMA8451:1 Faults")
            l0(iIndex).Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1

            'do the SC16IS devices
            For iCounter As Integer = 0 To 8 - 1
                l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("SC16:" & iCounter & " Faults")

                If iCounter = 0 Then
                    l0(iIndex).Layout__BelowControl(Me.m_txtFaults(iIndex - 3))
                Else
                    l0(iIndex).Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
                End If
                Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
                iIndex += 1
            Next

            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("ASI Faults")
            l0(iIndex).Layout__BelowControl(Me.m_txtFaults(iIndex - 8))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1

            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("Brakes Faults")
            l0(iIndex).Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1

            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("DAQ Faults")
            l0(iIndex).Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1


            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("Laser Contrast")
            l0(iIndex).Layout__BelowControl(Me.m_txtFaults(iIndex - 3))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1

            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("Contrast:0 Faults")
            l0(iIndex).Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1

            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("Contrast:1 Faults")
            l0(iIndex).Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1
            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("Contrast:2 Faults")
            l0(iIndex).Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1


            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("OptoNCDT Module")
            l0(iIndex).Layout__BelowControl(Me.m_txtFaults(iIndex - 4))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1


            'do the OptoNCDT's devices
            For iCounter As Integer = 0 To 6 - 1
                l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("NCDT:" & iCounter & " Faults")
                l0(iIndex).Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
                Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
                iIndex += 1
            Next


            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("Laser Distance")
            l0(iIndex).Layout__BelowControl(Me.m_txtFaults(iIndex - 7))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1

            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("Networking")
            l0(iIndex).Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1

            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("Pusher Faults")
            l0(iIndex).Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1

            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("AMC7812 Faults")
            l0(iIndex).Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1

            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("Throttle Faults")
            l0(iIndex).Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1

            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("Pod Health")
            l0(iIndex).Layout__BelowControl(Me.m_txtFaults(iIndex - 5))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            Me.m_txtFaults(iIndex).Flags__Add("P0: BATTERY_PACK_TEMP_RANGE")
            Me.m_txtFaults(iIndex).Flags__Add("P1: BATTERY_CELL_TEMP_RANGE")
            Me.m_txtFaults(iIndex).Flags__Add("P2: BATTERY_VOLTAGE_RANGE")
            Me.m_txtFaults(iIndex).Flags__Add("P3: BATTERY_CELL_VOLTAGE_RANGE")
            Me.m_txtFaults(iIndex).Flags__Add("P4: BATTERY_CURRENT_RANGE")
            Me.m_txtFaults(iIndex).Flags__Add("P5: HE_TEMP_RANGE")
            Me.m_txtFaults(iIndex).Flags__Add("P6: HE_CURRENT_RANGE")
            Me.m_txtFaults(iIndex).Flags__Add("P7: HE_VOLT_RANGE")
            Me.m_txtFaults(iIndex).Flags__Add("P8: HE_RPM_RANGE")
            Me.m_txtFaults(iIndex).Flags__Add("P9: PV_PRESS_RANGE")
            Me.m_txtFaults(iIndex).Flags__Add("P10: PV_TEMP_RANGE")
            iIndex += 1



            For iCounter As Integer = 0 To 3 - 1
                l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("Spare:" & iCounter & " Faults")

                If iCounter = 0 Then
                    l0(iIndex).Layout__BelowControl(Me.m_txtFaults(iIndex - 1))
                Else
                    l0(iIndex).Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
                End If
                Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
                iIndex += 1
            Next

            'flight controller
            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("Flight Control - Top")
            l0(iIndex).Layout__BelowControl(Me.m_txtFaults(iIndex - 3))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1

            l0(iIndex) = New SIL3.ApplicationSupport.LabelHelper("Track Database")
            l0(iIndex).Layout__AboveRightControl(l0(iIndex - 1), Me.m_txtFaults(iIndex - 1))
            Me.m_txtFaults(iIndex) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iIndex))
            iIndex += 1

        End Sub

#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        Private Sub btnEnableDAQ__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__DAQ_ENABLE,
                                                 1, 0, 0, 0)
        End Sub

        Private Sub btnBurstDAQ__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__DAQ_FLUSH,
                                                 0, 0, 0, 0)
        End Sub

        ''' <summary>
        ''' Request laser0 contrast data
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnRequest_L0__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LASER_CONT__REQUEST_LASER_DATA,
                                                 0, 0, 0, 0)
        End Sub
        Private Sub btnRequest_L1__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LASER_CONT__REQUEST_LASER_DATA,
                                                 1, 0, 0, 0)
        End Sub
        Private Sub btnRequest_L2__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LASER_CONT__REQUEST_LASER_DATA,
                                                 2, 0, 0, 0)
        End Sub



#End Region '#Region "BUTTON HELPERS"

    End Class


End Namespace
