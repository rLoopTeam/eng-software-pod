Namespace SIL3.rLoop.rPodControl.Panels.FlightControl

    ''' <summary>
    ''' Brakes Diagnostic System
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Brakes
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"
        Private Const C_NUM_BRAKES As Integer = 2
#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        Private m_iRxCount As Integer
        Private m_txtCount As SIL3.ApplicationSupport.TextBoxHelper


        Private m_txtFlags(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtSpares(C_NUM_BRAKES - 1, 5 - 1) As SIL3.ApplicationSupport.TextBoxHelper

        'switches
        Private m_txtLimitsExtend_State(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtLimitsRetract_State(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtLimitsExtend_EdgeSeen(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtLimitsRetract_EdgeSeen(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper

        'mlp
        Private m_txtMLP_ADC(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtMLP_ADCZero(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtMLP_ADCMinusZero(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtMLP_ADCSpan(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtMLP_Position_mm(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper

        'stepper system
        Private m_txtStep_Veloc(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtStep_Accel(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtStep_CurrentPos(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper


        Private m_txtDistRAW As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtDistFilt As SIL3.ApplicationSupport.TextBoxHelper

        ''' <summary>
        ''' The logging directory
        ''' </summary>
        Private m_sLogDir As String

        ''' <summary>
        ''' Allows us to write CSV logs of the edges
        ''' </summary>
        Private m_pCSV As SIL3.FileSupport.CSV


        ''' <summary>
        ''' Our DAQ Receiver
        ''' </summary>
        Private m_pDAQ As SIL3.DAQ.Top

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
            Me.m_sLogDir = Me.m_sLogDir & "LASER_DIST\"

            'check our folder
            SIL3.FileSupport.FileHelpers.Folder__CheckWarnMake(Me.m_sLogDir, True)

            'create the log files in prep
            'Me.m_pCSV = New SIL3.FileSupport.CSV(Me.m_sLogDir & "Laser0.csv", ",", False, False)
            'If Me.m_pCSV.File__Exists = False Then
            'End If


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

                'match thepacket
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__TX_DATA Then

                    Dim iOffset As Integer = 0

                    Dim pU32Flags(C_NUM_BRAKES - 1) As SIL3.Numerical.U32
                    Dim pU32Spare(C_NUM_BRAKES - 1, 5 - 1) As SIL3.Numerical.U32

                    For iCounter As Integer = 0 To C_NUM_BRAKES - 1

                        pU32Flags(iCounter) = New SIL3.Numerical.U32(u8Payload, iOffset)
                        iOffset += 4

                        pU32Spare(iCounter, 0) = New SIL3.Numerical.U32(u8Payload, iOffset)
                        iOffset += 4
                        pU32Spare(iCounter, 1) = New SIL3.Numerical.U32(u8Payload, iOffset)
                        iOffset += 4
                        pU32Spare(iCounter, 2) = New SIL3.Numerical.U32(u8Payload, iOffset)
                        iOffset += 4
                        pU32Spare(iCounter, 3) = New SIL3.Numerical.U32(u8Payload, iOffset)
                        iOffset += 4
                        pU32Spare(iCounter, 4) = New SIL3.Numerical.U32(u8Payload, iOffset)
                        iOffset += 4

                    Next

                    'update the GUI
                    For iCounter As Integer = 0 To C_NUM_BRAKES - 1
                        Me.m_txtFlags(iCounter).Threadsafe__SetText(pU32Flags(iCounter).To_String)
                        Me.m_txtSpares(iCounter, 0).Threadsafe__SetText(pU32Spare(iCounter, 0).To_String)
                        Me.m_txtSpares(iCounter, 1).Threadsafe__SetText(pU32Spare(iCounter, 1).To_String)
                        Me.m_txtSpares(iCounter, 2).Threadsafe__SetText(pU32Spare(iCounter, 2).To_String)
                        'Me.m_txtSpares(iCounter, 3).Threadsafe__SetText(pU32Spare(iCounter, 3).To_String)
                        'Me.m_txtSpares(iCounter, 4).Threadsafe__SetText(pU32Spare(iCounter, 4).To_String)
                    Next



                    Me.m_iRxCount += 1
                    Me.m_txtCount.Threadsafe__SetText(Me.m_iRxCount.ToString)


                End If
            End If

        End Sub


#End Region '#Region "EVENTS"

#Region "PANEL LAYOUT"

        ''' <summary>
        ''' generates a L/R
        ''' </summary>
        ''' <param name="iIndex"></param>
        ''' <returns></returns>
        Private Function Layout__GetBrakeSide(iIndex As Integer) As String
            If iIndex = 0 Then
                Return "L"
            Else
                Return "R"
            End If
        End Function

        ''' <summary>
        ''' Create our layout prior to being shown
        ''' </summary>
        ''' <remarks></remarks>
        Public Overrides Sub LayoutPanel()

            Dim l0(C_NUM_BRAKES - 1, 20) As SIL3.ApplicationSupport.LabelHelper

            Dim iDevice As Integer = 0

            'general
            l0(iDevice, 0) = New SIL3.ApplicationSupport.LabelHelper(10, 10, "Fault Flags " & Me.Layout__GetBrakeSide(iDevice), MyBase.m_pInnerPanel)
            Me.m_txtFlags(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 0))

            l0(iDevice, 1) = New SIL3.ApplicationSupport.LabelHelper("Spare " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 1).Layout__AboveRightControl(l0(iDevice, 0), Me.m_txtFlags(iDevice))
            Me.m_txtSpares(iDevice, 0) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 1))

            l0(iDevice, 2) = New SIL3.ApplicationSupport.LabelHelper("Spare " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 2).Layout__AboveRightControl(l0(iDevice, 1), Me.m_txtSpares(iDevice, 0))
            Me.m_txtSpares(iDevice, 1) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 2))

            l0(iDevice, 3) = New SIL3.ApplicationSupport.LabelHelper("Spare " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 3).Layout__AboveRightControl(l0(iDevice, 1), Me.m_txtSpares(iDevice, 1))
            Me.m_txtSpares(iDevice, 2) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 3))


            'switches
            l0(iDevice, 4) = New SIL3.ApplicationSupport.LabelHelper("Sw Ext State " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 4).Layout__BelowControl(Me.m_txtFlags(iDevice))
            Me.m_txtLimitsExtend_State(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 4))

            l0(iDevice, 5) = New SIL3.ApplicationSupport.LabelHelper("Sw Retract State " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 5).Layout__AboveRightControl(l0(iDevice, 4), Me.m_txtLimitsExtend_State(iDevice))
            Me.m_txtLimitsRetract_State(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 5))


            l0(iDevice, 6) = New SIL3.ApplicationSupport.LabelHelper("Sw Ext Edge " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 6).Layout__BelowControl(Me.m_txtLimitsExtend_State(iDevice))
            Me.m_txtLimitsExtend_EdgeSeen(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 6))

            l0(iDevice, 7) = New SIL3.ApplicationSupport.LabelHelper("Sw Retract Edge " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 7).Layout__AboveRightControl(l0(iDevice, 6), Me.m_txtLimitsExtend_EdgeSeen(iDevice))
            Me.m_txtLimitsRetract_EdgeSeen(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 7))


            'mlp
            l0(iDevice, 8) = New SIL3.ApplicationSupport.LabelHelper("MLP ADC " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 8).Layout__BelowControl(Me.m_txtLimitsExtend_EdgeSeen(iDevice))
            Me.m_txtMLP_ADC(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 8))

            l0(iDevice, 9) = New SIL3.ApplicationSupport.LabelHelper("MLP ADC Zero " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 9).Layout__AboveRightControl(l0(iDevice, 8), Me.m_txtMLP_ADC(iDevice))
            Me.m_txtMLP_ADCZero(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 9))

            l0(iDevice, 10) = New SIL3.ApplicationSupport.LabelHelper("MLP ADC Span " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 10).Layout__AboveRightControl(l0(iDevice, 8), Me.m_txtMLP_ADCZero(iDevice))
            Me.m_txtMLP_ADCSpan(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 10))

            l0(iDevice, 11) = New SIL3.ApplicationSupport.LabelHelper("MLP Position(mm) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 11).Layout__AboveRightControl(l0(iDevice, 10), Me.m_txtMLP_ADCSpan(iDevice))
            Me.m_txtMLP_Position_mm(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 11))


            'stepper
            l0(iDevice, 12) = New SIL3.ApplicationSupport.LabelHelper("Stepper Veloc " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 12).Layout__BelowControl(Me.m_txtMLP_ADC(iDevice))
            Me.m_txtStep_Veloc(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 12))

            l0(iDevice, 13) = New SIL3.ApplicationSupport.LabelHelper("Stepper Accel " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 13).Layout__AboveRightControl(l0(iDevice, 12), Me.m_txtStep_Veloc(iDevice))
            Me.m_txtStep_Accel(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 13))

            l0(iDevice, 14) = New SIL3.ApplicationSupport.LabelHelper("Stepper Pos " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 14).Layout__AboveRightControl(l0(iDevice, 12), Me.m_txtStep_Accel(iDevice))
            Me.m_txtStep_CurrentPos(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 14))





            iDevice = 1
            'general
            l0(iDevice, 0) = New SIL3.ApplicationSupport.LabelHelper("Fault Flags " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 0).Layout__AboveRightControl(l0(iDevice - 1, 0), Me.m_txtSpares(iDevice - 1, 2))
            Me.m_txtFlags(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 0))

            l0(iDevice, 1) = New SIL3.ApplicationSupport.LabelHelper("Spare " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 1).Layout__AboveRightControl(l0(iDevice, 0), Me.m_txtFlags(iDevice))
            Me.m_txtSpares(iDevice, 0) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 1))

            l0(iDevice, 2) = New SIL3.ApplicationSupport.LabelHelper("Spare " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 2).Layout__AboveRightControl(l0(iDevice, 1), Me.m_txtSpares(iDevice, 0))
            Me.m_txtSpares(iDevice, 1) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 2))

            l0(iDevice, 3) = New SIL3.ApplicationSupport.LabelHelper("Spare " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 3).Layout__AboveRightControl(l0(iDevice, 1), Me.m_txtSpares(iDevice, 1))
            Me.m_txtSpares(iDevice, 2) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 3))

            'switches
            l0(iDevice, 4) = New SIL3.ApplicationSupport.LabelHelper("Sw Ext State " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 4).Layout__BelowControl(Me.m_txtFlags(iDevice))
            Me.m_txtLimitsExtend_State(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 4))

            l0(iDevice, 5) = New SIL3.ApplicationSupport.LabelHelper("Sw Retract State " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 5).Layout__AboveRightControl(l0(iDevice, 4), Me.m_txtLimitsExtend_State(iDevice))
            Me.m_txtLimitsRetract_State(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 5))


            l0(iDevice, 6) = New SIL3.ApplicationSupport.LabelHelper("Sw Ext Edge " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 6).Layout__BelowControl(Me.m_txtLimitsExtend_State(iDevice))
            Me.m_txtLimitsExtend_EdgeSeen(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 6))

            l0(iDevice, 7) = New SIL3.ApplicationSupport.LabelHelper("Sw Retract Edge " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 7).Layout__AboveRightControl(l0(iDevice, 6), Me.m_txtLimitsExtend_EdgeSeen(iDevice))
            Me.m_txtLimitsRetract_EdgeSeen(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 7))

            'mlp
            l0(iDevice, 8) = New SIL3.ApplicationSupport.LabelHelper("MLP ADC " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 8).Layout__BelowControl(Me.m_txtLimitsExtend_EdgeSeen(iDevice))
            Me.m_txtMLP_ADC(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 8))

            l0(iDevice, 9) = New SIL3.ApplicationSupport.LabelHelper("MLP ADC Zero " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 9).Layout__AboveRightControl(l0(iDevice, 8), Me.m_txtMLP_ADC(iDevice))
            Me.m_txtMLP_ADCZero(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 9))

            l0(iDevice, 10) = New SIL3.ApplicationSupport.LabelHelper("MLP ADC Span " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 10).Layout__AboveRightControl(l0(iDevice, 8), Me.m_txtMLP_ADCZero(iDevice))
            Me.m_txtMLP_ADCSpan(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 10))

            l0(iDevice, 11) = New SIL3.ApplicationSupport.LabelHelper("MLP Position(mm) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 11).Layout__AboveRightControl(l0(iDevice, 10), Me.m_txtMLP_ADCSpan(iDevice))
            Me.m_txtMLP_Position_mm(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 11))

            'stepper
            l0(iDevice, 12) = New SIL3.ApplicationSupport.LabelHelper("Stepper Veloc " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 12).Layout__BelowControl(Me.m_txtMLP_ADC(iDevice))
            Me.m_txtStep_Veloc(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 12))

            l0(iDevice, 13) = New SIL3.ApplicationSupport.LabelHelper("Stepper Accel " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 13).Layout__AboveRightControl(l0(iDevice, 12), Me.m_txtStep_Veloc(iDevice))
            Me.m_txtStep_Accel(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 13))

            l0(iDevice, 14) = New SIL3.ApplicationSupport.LabelHelper("Stepper Pos " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 14).Layout__AboveRightControl(l0(iDevice, 12), Me.m_txtStep_Accel(iDevice))
            Me.m_txtStep_CurrentPos(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 14))




            Dim l11 As New SIL3.ApplicationSupport.LabelHelper("Rx Count")
            l11.Layout__BelowControl(Me.m_txtStep_Veloc(0))
            Me.m_txtCount = New SIL3.ApplicationSupport.TextBoxHelper(100, l11)

            Dim btnOn As New SIL3.ApplicationSupport.ButtonHelper(100, "Stream On", AddressOf btnStreamOn__Click)
            btnOn.Layout__BelowControl(Me.m_txtCount)

            Dim btnOff As New SIL3.ApplicationSupport.ButtonHelper(100, "Stream Off", AddressOf btnStreamOff__Click)
            btnOff.Layout__RightOfControl(btnOn)


        End Sub

#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        Private Sub btnStreamOn__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 1, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__TX_DATA, 0, 0)
        End Sub

        Private Sub btnStreamOff__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 0, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__TX_DATA, 0, 0)
        End Sub



#End Region '#Region "BUTTON HELPERS"

    End Class


End Namespace
