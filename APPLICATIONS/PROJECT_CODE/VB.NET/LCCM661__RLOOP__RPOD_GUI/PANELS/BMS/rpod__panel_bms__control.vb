Namespace SIL3.rLoop.rPodControl.Panels.BMS

    ''' <summary>
    ''' BMS Control
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Control
	        Inherits LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"
        Private Const C_NUM_BQ76 As Integer = 3
        Private Const C_NUM_CELLS As Integer = 18
#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        Private m_txtBMS_FaultFlags As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags
        Private m_txtBQ76_FaultFlags(C_NUM_BQ76 - 1) As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags

        Private m_txtRxCount As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_S32
        Private m_iRxCount As Integer


        Private m_txtPackVolts As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtCell_Highest As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtCell_Lowest As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtBatt_Current As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32

        ''' <summary>
        ''' The current bms channel
        ''' </summary>
        Private m_iBMSIndex As Integer

#End Region '#Region "MEMBERS"

#Region "NEW"
        ''' <summary>
        ''' New instance
        ''' </summary>
        ''' <param name="sPanelText"></param>
        ''' <remarks></remarks>
        Public Sub New(sPanelText As String, iBMSIndex As Integer)
            MyBase.New(sPanelText)

            Me.m_iBMSIndex = iBMSIndex

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

            Dim l1 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper(10, 10, "BMS Flags", Me.m_pInnerPanel)
            Me.m_txtBMS_FaultFlags = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l1)
            Me.m_txtBMS_FaultFlags.FlagsFile__Read("../../../../FIRMWARE/PROJECT_CODE/LCCM653__RLOOP__POWER_CORE/power_core__fault_flags.h", "CORE")

            Dim l1a As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Rx Packets")
            l1a.Layout__AboveRightControl(l1, Me.m_txtBMS_FaultFlags)
            Me.m_txtRxCount = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_S32(100, l1a)

            Dim l2a As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("BQ76:0 Flags")
            l2a.Layout__BelowControl(Me.m_txtBMS_FaultFlags)
            Me.m_txtBQ76_FaultFlags(0) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l2a)
            Me.m_txtBQ76_FaultFlags(0).FlagsFile__Read("../../../../FIRMWARE/COMMON_CODE/MULTICORE/LCCM715__MULTICORE__BQ76PL536A/bq76__device_fault_flags.h", "DEVICE")

            Dim l2b As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("BQ76:1 Flags")
            l2b.Layout__AboveRightControl(l2a, Me.m_txtBQ76_FaultFlags(0))
            Me.m_txtBQ76_FaultFlags(1) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l2b)
            Me.m_txtBQ76_FaultFlags(1).FlagsFile__Read("../../../../FIRMWARE/COMMON_CODE/MULTICORE/LCCM715__MULTICORE__BQ76PL536A/bq76__device_fault_flags.h", "DEVICE")

            Dim l2c As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("BQ76:2 Flags")
            l2c.Layout__AboveRightControl(l2b, Me.m_txtBQ76_FaultFlags(1))
            Me.m_txtBQ76_FaultFlags(2) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l2c)
            Me.m_txtBQ76_FaultFlags(2).FlagsFile__Read("../../../../FIRMWARE/COMMON_CODE/MULTICORE/LCCM715__MULTICORE__BQ76PL536A/bq76__device_fault_flags.h", "DEVICE")

            Dim l6 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Pack Volts", Me.m_txtBQ76_FaultFlags(0))
            Me.m_txtPackVolts = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(100, l6)
            Me.m_txtPackVolts.Limits__SetUpper(76.0)

            Dim l7 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Highest Cell V")
            l7.Layout__AboveRightControl(l6, Me.m_txtPackVolts)
            Me.m_txtCell_Highest = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(100, l7)
            Me.m_txtCell_Highest.Limits__SetUpper(4.3)

            Dim l8 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Lowest Cell V")
            l8.Layout__AboveRightControl(l7, Me.m_txtCell_Highest)
            Me.m_txtCell_Lowest = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(100, l8)
            Me.m_txtCell_Lowest.Limits__SetLower(3.2)

            Dim btnLatch As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Latch", AddressOf Me.btnlatch_Click)
            btnLatch.Layout__BelowControl(Me.m_txtPackVolts)

            Dim btnSafe As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Safe", AddressOf Me.btnSafe_Click)
            btnSafe.Layout__RightOfControl(btnLatch)


        End Sub
#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON"

        ''' <summary>
        ''' Latch on the power node to the bus
        ''' </summary>
        ''' <param name="sender"></param>
        ''' <param name="e"></param>
        Private Sub btnlatch_Click(sender As Object, e As EventArgs)

            Dim pPoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS = Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__BMS_A
            If Me.m_iBMSIndex <> 0 Then
                pPoint = Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__BMS_B
            End If
            RaiseEvent UserEvent__SafeUDP__Tx_X4(pPoint,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__PWR_GEN__LATCH,
                                                 &HABCD1245L,
                                                 Me.m_iBMSIndex,
                                                 0, 0)


        End Sub

        ''' <summary>
        ''' Pod safe
        ''' </summary>
        ''' <param name="sender"></param>
        ''' <param name="e"></param>
        Private Sub btnSafe_Click(sender As Object, e As EventArgs)

            Dim pPoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS = Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__BMS_A
            If Me.m_iBMSIndex <> 0 Then
                pPoint = Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__BMS_B
            End If
            RaiseEvent UserEvent__SafeUDP__Tx_X4(pPoint,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__PWR_GEN__POD_SAFE_COMMAND,
                                                 &H76543210L,
                                                 0,
                                                 0, 0)


        End Sub


        Private Sub btnDischg_Click(sender As Object, e As EventArgs)

            Dim pPoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS = Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__BMS_A
            If Me.m_iBMSIndex <> 0 Then
                pPoint = Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__BMS_B
            End If

            'get our button details
            Dim pB As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper = CType(sender, LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper)
            Dim iIndex As Integer = CInt(pB.Tag)

            If pB.Text = "Resistor Off" Then
                pB.Text = "Resistor On"

                RaiseEvent UserEvent__SafeUDP__Tx_X4(pPoint,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__PWR_GEN__MANUAL_BALANCE_CONTROL,
                                                 &H34566543L,
                                                 1,
                                                 iIndex, 0)


            Else
                pB.Text = "Resistor Off"

                RaiseEvent UserEvent__SafeUDP__Tx_X4(pPoint,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__PWR_GEN__MANUAL_BALANCE_CONTROL,
                                                 &H34566543L,
                                                 1,
                                                 iIndex, 1)


            End If





        End Sub

        Private Sub btnCharge_Disable(sender As Object, e As EventArgs)


            Dim pPoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS = Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__BMS_A
            If Me.m_iBMSIndex <> 0 Then
                pPoint = Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__BMS_B
            End If

            RaiseEvent UserEvent__SafeUDP__Tx_X4(pPoint,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__PWR_GEN__CHARGER_CONTROL,
                                                 &H11229988L,
                                                 0,
                                                 0, 0)

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
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__PWR_BMS__TX_BMS_STATUS Then

                    Dim iOffset As Integer = 0

                    'top flags
                    iOffset += Me.m_txtBMS_FaultFlags.Flags__Update(u8Payload, iOffset, True)

                    'Bq76 flags
                    iOffset += Me.m_txtBQ76_FaultFlags(0).Flags__Update(u8Payload, iOffset, True)
                    iOffset += Me.m_txtBQ76_FaultFlags(1).Flags__Update(u8Payload, iOffset, True)
                    iOffset += Me.m_txtBQ76_FaultFlags(2).Flags__Update(u8Payload, iOffset, True)

                    iOffset += Me.m_txtPackVolts.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtCell_Highest.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtCell_Lowest.Value__Update(u8Payload, iOffset)

                    'cell volts
                    For iCounter As Integer = 0 To C_NUM_CELLS - 1
                        iOffset += 4
                    Next

                    'cell spares
                    iOffset += 18 * 4

                    'resistors
                    iOffset += 18

                    'volts update count
                    iOffset += 4

                    'batt spares
                    iOffset += 4

                    'charger state
                    iOffset += 0

                    'temp sensor state
                    iOffset += 1

                    'num sensors
                    iOffset += 2

                    'highest temp
                    iOffset += 4 ' Me.m_txtHighestTemp.Value__Update(u8Payload, iOffset)
                    iOffset += 4 ' Me.m_txtAverageTemp.Value__Update(u8Payload, iOffset)

                    'highest sensor index
                    iOffset += 2

                    'temp scan count


                    Me.m_iRxCount += 1
                    Me.m_txtRxCount.Threadsafe__SetText(Me.m_iRxCount.ToString)


                End If
            End If

        End Sub

#End Region '#Region "ETH RX"


    End Class


End Namespace
