Namespace SIL3.rLoop.rPodControl.Panels.BMS

    ''' <summary>
    ''' Manual BMS Charger Control
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Charger
	        Inherits LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.PanelTemplate

#Region "MEMBERS"

        ''' <summary>
        ''' Power node faults
        ''' </summary>
        Private m_txtNode_FaultFlags As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags


        Private m_txtCharger_State As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_StateDisplay

        Private m_txtHighestTemp As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtAverageTemp As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32

        Private m_txtPackVolts As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtCell_Highest As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtCell_Lowest As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32


        Private m_txtRxCount As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_S32
        Private m_iRxCount As Integer


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

            Dim l1 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper(10, 10, "Fault Flags", Me.m_pInnerPanel)
            Me.m_txtNode_FaultFlags = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l1)
            Me.m_txtNode_FaultFlags.FlagsFile__Read("../../../../FIRMWARE/PROJECT_CODE/LCCM653__RLOOP__POWER_CORE/power_core__fault_flags.h", "CORE")


            Dim l1a As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Rx Packets")
            l1a.Layout__AboveRightControl(l1, Me.m_txtNode_FaultFlags)
            Me.m_txtRxCount = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_S32(100, l1a)


            Dim l2a As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Manual Charge Control", Me.m_txtNode_FaultFlags)
            Dim btnCharger_Enable As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Enable", AddressOf Me.btnCharge_Enable)
            btnCharger_Enable.Layout__BelowControl(l2a)
            Dim btnCharger_Disable As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Disable", AddressOf Me.btnCharge_Disable)
            btnCharger_Disable.Layout__RightOfControl(btnCharger_Enable)

            Dim l3 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Charger State", btnCharger_Enable)
            Me.m_txtCharger_State = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_StateDisplay(400, l3)
            Me.m_txtCharger_State.HeaderFile__Set("../../../../FIRMWARE/PROJECT_CODE/LCCM653__RLOOP__POWER_CORE/power_core__state_types.h", "TE_PWR__CHARGER_STATE_T")

            Dim l4 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Highest °C", m_txtCharger_State)
            Me.m_txtHighestTemp = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(100, l4)
            Me.m_txtHighestTemp.Limits__SetUpper(60.0)

            Dim l5 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Average °C")
            l5.Layout__AboveRightControl(l4, Me.m_txtHighestTemp)
            Me.m_txtAverageTemp = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(100, l5)
            Me.m_txtAverageTemp.Limits__SetUpper(60.0)


            Dim l6 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Pack Volts", m_txtHighestTemp)
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



        End Sub
#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON"


        Private Sub btnCharge_Enable(sender As Object, e As EventArgs)

            Dim pPoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS = Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__BMS_A
            If Me.m_iBMSIndex <> 0 Then
                pPoint = Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__BMS_B
            End If

            RaiseEvent UserEvent__SafeUDP__Tx_X4(pPoint,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__PWR_GEN__CHARGER_CONTROL,
                                                 &H11229988L,
                                                 1,
                                                 0, 0)

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
                    iOffset += Me.m_txtNode_FaultFlags.Flags__Update(u8Payload, iOffset, True)

                    'Bq76 flags
                    iOffset += 12

                    iOffset += Me.m_txtPackVolts.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtCell_Highest.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtCell_Lowest.Value__Update(u8Payload, iOffset)

                    'cell volts
                    iOffset += 18 * 4

                    'cell spares
                    iOffset += 18 * 4

                    'resistors
                    iOffset += 18

                    'volts update count
                    iOffset += 4

                    'batt spares
                    iOffset += 4

                    'charger state
                    iOffset += Me.m_txtCharger_State.Value__UpdateU8(u8Payload, iOffset)

                    'temp sensor state
                    iOffset += 1

                    'num sensors
                    iOffset += 2

                    'highest temp
                    iOffset += Me.m_txtHighestTemp.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtAverageTemp.Value__Update(u8Payload, iOffset)

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
