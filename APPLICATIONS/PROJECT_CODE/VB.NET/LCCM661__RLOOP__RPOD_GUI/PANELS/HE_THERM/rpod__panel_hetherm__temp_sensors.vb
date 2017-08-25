Namespace SIL3.rLoop.rPodControl.Panels.HETherm

    ''' <summary>
    ''' Temperature Sensor Monitoring
    ''' </summary>
    ''' <remarks></remarks>
    Public Class TempSensors
	        Inherits LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"
        ''' <summary>
        ''' Total number of sensors in the system, don't touch this
        ''' </summary>
        Private Const C_NUM_TEMP_SENSORS As Integer = 24

#End Region '#Region "CONSTANTS"

#Region "MEMBERS"


        Private m_txtRxCount As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_S32

        Private m_txtNumSensors As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U8
        Private m_txtTemperature(C_NUM_TEMP_SENSORS - 1) As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtROM(C_NUM_TEMP_SENSORS - 1) As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper

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
                Me.m_txtTemperature(iIndex) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(120, l7(iIndex))
                iIndex += 1
            Next

            iIndex = 0
            Dim l8(C_NUM_TEMP_SENSORS - 1) As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper
            For iCounter As Integer = 0 To C_NUM_TEMP_SENSORS - 1
                l8(iIndex) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("ROM " & iIndex.ToString("00"))
                If iIndex = 0 Then
                    l8(iIndex).Layout__BelowControl(Me.m_txtTemperature(16))
                ElseIf iIndex = 8 Then
                    l8(iIndex).Layout__BelowControl(Me.m_txtROM(iIndex - 8))
                ElseIf iIndex = 16 Then
                    l8(iIndex).Layout__BelowControl(Me.m_txtROM(iIndex - 8))
                ElseIf iIndex = 24 Then
                    l8(iIndex).Layout__BelowControl(Me.m_txtROM(iIndex - 8))
                Else
                    l8(iIndex).Layout__AboveRightControl(l8(iIndex - 1), Me.m_txtROM(iIndex - 1))
                End If
                Me.m_txtROM(iIndex) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(120, l8(iIndex))
                iIndex += 1
            Next

        End Sub
#End Region '#Region "PANEL LAYOUT"

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

                    iOffset += 4 'Me.m_txtFaultFlags_TOP.Flags__Update(u8Payload, iOffset, True)
                    iOffset += 4 'Me.m_txtFaultFlags_Solenoid.Flags__Update(u8Payload, iOffset, True)
                    iOffset += 4 'Me.m_txtFaultFlags_DS2482_0.Flags__Update(u8Payload, iOffset, True)
                    iOffset += 4 'Me.m_txtFaultFlags_DS2482_1.Flags__Update(u8Payload, iOffset, True)
                    iOffset += 4 'Me.m_txtFaultFlags_DS18B20.Flags__Update(u8Payload, iOffset, True)
                    iOffset += Me.m_txtNumSensors.Value__Update(u8Payload, iOffset)

                    'sensors
                    For iCounter As Integer = 0 To C_NUM_TEMP_SENSORS - 1
                        iOffset += Me.m_txtTemperature(iCounter).Value__Update(u8Payload, iOffset)

                        If Me.m_txtTemperature(iCounter).Text = "2047.7500" Then
                            Me.m_txtTemperature(iCounter).BackColor = Color.Orange
                        Else
                            Me.m_txtTemperature(iCounter).BackColor = Color.White
                        End If

                        'RomID
                        Dim pU8A As New LAPP188__RLOOP__LIB.SIL3.Numerical.U8Array(u8Payload, iOffset, 8)
                        iOffset += 8
                        Me.m_txtROM(iCounter).Threadsafe__SetText(pU8A.To_String__FormattedHex)


                    Next

                    Me.m_iRxCount += 1
                    Me.m_txtRxCount.Threadsafe__SetText(Me.m_iRxCount.ToString)


                End If
            End If

        End Sub

#End Region '#Region "ETH RX"

    End Class


End Namespace
