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

        Private m_txtTargetIBeam(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtTargetScrew_mm(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtTargetScrew_um(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper

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


        Private m_txtBrakeState As SIL3.ApplicationSupport.TextBoxHelper

        Private m_txtDevRawMove As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtDevIBeamMove As SIL3.ApplicationSupport.TextBoxHelper

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
                    Dim pU32Spare(C_NUM_BRAKES - 1, 2 - 1) As SIL3.Numerical.U32

                    Dim pF32TargetIBeam(C_NUM_BRAKES - 1) As SIL3.Numerical.F32
                    Dim pF32TargetScrew_mm(C_NUM_BRAKES - 1) As SIL3.Numerical.F32
                    Dim pS32TargetScrew_um(C_NUM_BRAKES - 1) As SIL3.Numerical.S32

                    Dim pu8LimitsExtend_State(C_NUM_BRAKES - 1) As SIL3.Numerical.U8
                    Dim pu8LimitsRetract_State(C_NUM_BRAKES - 1) As SIL3.Numerical.U8
                    Dim pu8LimitsExtend_EdgeSeen(C_NUM_BRAKES - 1) As SIL3.Numerical.U8
                    Dim pu8LimitsRetract_EdgeSeen(C_NUM_BRAKES - 1) As SIL3.Numerical.U8


                    Dim pu16ADC_Sample(C_NUM_BRAKES - 1) As SIL3.Numerical.U16
                    Dim pu16ADC_Zero(C_NUM_BRAKES - 1) As SIL3.Numerical.U16
                    Dim pf32ADC_Span(C_NUM_BRAKES - 1) As SIL3.Numerical.F32
                    Dim pf32ADC_MLPPos(C_NUM_BRAKES - 1) As SIL3.Numerical.F32

                    Dim ps32Step_Veloc(C_NUM_BRAKES - 1) As SIL3.Numerical.S32
                    Dim ps32Step_Accel(C_NUM_BRAKES - 1) As SIL3.Numerical.S32
                    Dim ps32Step_CurrentPos(C_NUM_BRAKES - 1) As SIL3.Numerical.S32

                    Dim pu8BrakeState As SIL3.Numerical.U8

                    For iCounter As Integer = 0 To C_NUM_BRAKES - 1

                        pU32Flags(iCounter) = New SIL3.Numerical.U32(u8Payload, iOffset)
                        iOffset += 4

                        pF32TargetIBeam(iCounter) = New SIL3.Numerical.F32(u8Payload, iOffset)
                        iOffset += 4
                        pF32TargetScrew_mm(iCounter) = New SIL3.Numerical.F32(u8Payload, iOffset)
                        iOffset += 4
                        pS32TargetScrew_um(iCounter) = New SIL3.Numerical.S32(u8Payload, iOffset)
                        iOffset += 4

                        pU32Spare(iCounter, 0) = New SIL3.Numerical.U32(u8Payload, iOffset)
                        iOffset += 4
                        pU32Spare(iCounter, 1) = New SIL3.Numerical.U32(u8Payload, iOffset)
                        iOffset += 4

                        'switches
                        pu8LimitsExtend_State(iCounter) = New SIL3.Numerical.U8(u8Payload, iOffset)
                        iOffset += 1
                        pu8LimitsRetract_State(iCounter) = New SIL3.Numerical.U8(u8Payload, iOffset)
                        iOffset += 1
                        pu8LimitsExtend_EdgeSeen(iCounter) = New SIL3.Numerical.U8(u8Payload, iOffset)
                        iOffset += 1
                        pu8LimitsRetract_EdgeSeen(iCounter) = New SIL3.Numerical.U8(u8Payload, iOffset)
                        iOffset += 1

                        'sw error
                        iOffset += 1


                        pu16ADC_Sample(iCounter) = New SIL3.Numerical.U16(u8Payload, iOffset)
                        iOffset += 2
                        pu16ADC_Zero(iCounter) = New SIL3.Numerical.U16(u8Payload, iOffset)
                        iOffset += 2

                        'adc minus zero
                        iOffset += 4

                        pf32ADC_Span(iCounter) = New SIL3.Numerical.F32(u8Payload, iOffset)
                        iOffset += 4
                        pf32ADC_MLPPos(iCounter) = New SIL3.Numerical.F32(u8Payload, iOffset)
                        iOffset += 4

                        'stepper
                        ps32Step_Veloc(iCounter) = New SIL3.Numerical.S32(u8Payload, iOffset)
                        iOffset += 4
                        ps32Step_Accel(iCounter) = New SIL3.Numerical.S32(u8Payload, iOffset)
                        iOffset += 4
                        ps32Step_CurrentPos(iCounter) = New SIL3.Numerical.S32(u8Payload, iOffset)
                        iOffset += 4

                    Next

                    pu8BrakeState = New SIL3.Numerical.U8(u8Payload, iOffset)
                    iOffset += 1


                    'update the GUI
                    For iCounter As Integer = 0 To C_NUM_BRAKES - 1
                        Me.m_txtFlags(iCounter).Threadsafe__SetText(pU32Flags(iCounter).To_String)
                        Me.m_txtTargetIBeam(iCounter).Threadsafe__SetText(pF32TargetIBeam(iCounter).To__Float32.ToString("0.000"))
                        Me.m_txtTargetScrew_mm(iCounter).Threadsafe__SetText(pF32TargetScrew_mm(iCounter).To__Float32.ToString("0.000"))
                        Me.m_txtTargetScrew_um(iCounter).Threadsafe__SetText(pS32TargetScrew_um(iCounter).To__Int.ToString)
                        'Me.m_txtSpares(iCounter, 3).Threadsafe__SetText(pU32Spare(iCounter, 3).To_String)
                        'Me.m_txtSpares(iCounter, 4).Threadsafe__SetText(pU32Spare(iCounter, 4).To_String)

                        Me.m_txtLimitsExtend_State(iCounter).Threadsafe__SetText(State__SwitchExtended(pu8LimitsExtend_State(iCounter)))
                        Me.m_txtLimitsRetract_State(iCounter).Threadsafe__SetText(State__SwitchExtended(pu8LimitsRetract_State(iCounter)))
                        Me.m_txtLimitsExtend_EdgeSeen(iCounter).Threadsafe__SetText(pu8LimitsExtend_EdgeSeen(iCounter).To_String)
                        Me.m_txtLimitsRetract_EdgeSeen(iCounter).Threadsafe__SetText(pu8LimitsRetract_EdgeSeen(iCounter).To_String)

                        'mlp
                        Me.m_txtMLP_ADC(iCounter).Threadsafe__SetText(pu16ADC_Sample(iCounter).To__Int)
                        Me.m_txtMLP_ADCZero(iCounter).Threadsafe__SetText(pu16ADC_Zero(iCounter).To__Int)
                        'Me.m_txtMLP_ADCMinusZero(iCounter).Threadsafe__SetText()
                        Me.m_txtMLP_ADCSpan(iCounter).Threadsafe__SetText(pf32ADC_Span(iCounter).To__Float32.ToString("0.0000"))
                        Me.m_txtMLP_Position_mm(iCounter).Threadsafe__SetText(pf32ADC_MLPPos(iCounter).To__Float32.ToString("0.0000"))

                        'stepper
                        Me.m_txtStep_Veloc(iCounter).Threadsafe__SetText(ps32Step_Veloc(iCounter).To__Int)
                        Me.m_txtStep_Accel(iCounter).Threadsafe__SetText(ps32Step_Accel(iCounter).To__Int)
                        Me.m_txtStep_CurrentPos(iCounter).Threadsafe__SetText(ps32Step_CurrentPos(iCounter).To__Int32.ToString)


                    Next

                    'brake state
                    Me.m_txtBrakeState.Threadsafe__SetText(State__Brake(pu8BrakeState))

                    Me.m_iRxCount += 1
                    Me.m_txtCount.Threadsafe__SetText(Me.m_iRxCount.ToString)


                End If
            End If

        End Sub

        ''' <summary>
        ''' return the brakes states
        ''' </summary>
        ''' <param name="u8Val"></param>
        ''' <returns></returns>
        Private Function State__Brake(u8Val As Numerical.U8) As String

            Select Case u8Val.To__Int
                Case 0
                    Return "BRAKE_STATE__RESET"
                Case 1
                    Return "BRAKE_STATE__IDLE"
                Case 2
                    Return "BRAKE_STATE__BEGIN_MOVE"
                Case 3
                    Return "BRAKE_STATE__COMPUTE"
                Case 4
                    Return "BRAKE_STATE__MOVING"
                Case 5
                    Return "BRAKE_STATE__MOVE_STOPPED"
                Case 6
                    Return "BRAKE_STATE__FAULT"
                Case 7
                    Return "BRAKE_STATE__TEST"
                Case 8
                    Return "BRAKE_STATE__BEGIN_CAL"
                Case 9
                    Return "BRAKE_STATE__WAIT_CAL_DONE"

                Case Else
                    Return "VB.NET ERROR"


            End Select

        End Function


        ''' <summary>
        ''' Convert switch state
        ''' </summary>
        ''' <param name="u8Val"></param>
        ''' <returns></returns>
        Private Function State__SwitchExtended(u8Val As Numerical.U8) As String

            Select Case u8Val.To__Int
                Case 0
                    Return "UNKNOWN"
                Case 1
                    Return "CLOSED"
                Case 2
                    Return "OPEN"
                Case Else
                    Return "VB.NET ERROR"
            End Select

        End Function

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

            l0(iDevice, 1) = New SIL3.ApplicationSupport.LabelHelper("Target IBeam " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 1).Layout__AboveRightControl(l0(iDevice, 0), Me.m_txtFlags(iDevice))
            Me.m_txtTargetIBeam(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 1))

            l0(iDevice, 2) = New SIL3.ApplicationSupport.LabelHelper("Target Screw (mm) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 2).Layout__AboveRightControl(l0(iDevice, 1), Me.m_txtTargetIBeam(iDevice))
            Me.m_txtTargetScrew_mm(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 2))

            l0(iDevice, 3) = New SIL3.ApplicationSupport.LabelHelper("Target Screw (um) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 3).Layout__AboveRightControl(l0(iDevice, 1), Me.m_txtTargetScrew_mm(iDevice))
            Me.m_txtTargetScrew_um(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 3))


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
            l0(iDevice, 0).Layout__AboveRightControl(l0(iDevice - 1, 0), Me.m_txtTargetScrew_um(iDevice - 1))
            Me.m_txtFlags(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 0))

            l0(iDevice, 1) = New SIL3.ApplicationSupport.LabelHelper("Target IBeam " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 1).Layout__AboveRightControl(l0(iDevice, 0), Me.m_txtFlags(iDevice))
            Me.m_txtTargetIBeam(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 1))

            l0(iDevice, 2) = New SIL3.ApplicationSupport.LabelHelper("Target Screw (mm) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 2).Layout__AboveRightControl(l0(iDevice, 1), Me.m_txtTargetIBeam(iDevice))
            Me.m_txtTargetScrew_mm(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 2))

            l0(iDevice, 3) = New SIL3.ApplicationSupport.LabelHelper("Target Screw (um) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, 3).Layout__AboveRightControl(l0(iDevice, 1), Me.m_txtTargetScrew_mm(iDevice))
            Me.m_txtTargetScrew_um(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, 3))

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


            Dim l10 As New SIL3.ApplicationSupport.LabelHelper("Brakes State")
            l10.Layout__BelowControl(Me.m_txtStep_Veloc(0))
            Me.m_txtBrakeState = New SIL3.ApplicationSupport.TextBoxHelper(200, l10)

            Dim l11 As New SIL3.ApplicationSupport.LabelHelper("Rx Count")
            l11.Layout__BelowControl(Me.m_txtBrakeState)
            Me.m_txtCount = New SIL3.ApplicationSupport.TextBoxHelper(100, l11)

            Dim btnOn As New SIL3.ApplicationSupport.ButtonHelper(100, "Stream On", AddressOf btnStreamOn__Click)
            btnOn.Layout__BelowControl(Me.m_txtCount)

            Dim btnOff As New SIL3.ApplicationSupport.ButtonHelper(100, "Stream Off", AddressOf btnStreamOff__Click)
            btnOff.Layout__RightOfControl(btnOn)

            Dim btnInit As New SIL3.ApplicationSupport.ButtonHelper(100, "Init Brakes", AddressOf btnInit__Click)
            btnInit.Layout__RightOfControl(btnOff)
            btnInit.ToolTip__Set("Brake Init", "This is required after reset")


            Dim btnDevEnable As New SIL3.ApplicationSupport.ButtonHelper(100, "Dev Enable", AddressOf btnDevEnable__Click)
            btnDevEnable.Layout__RightOfControl(btnInit)
            btnDevEnable.ToolTip__Set("Development Enable", "Use this to enable development mode before any manual brake commands can be sent.")

            Dim btnCal As New SIL3.ApplicationSupport.ButtonHelper(100, "Calibrate", AddressOf btnCalibrate__Click)
            btnCal.Layout__RightOfControl(btnDevEnable)
            btnCal.ToolTip__Set("Calibration", "Calibrate the brakes (Only works in DEV mode)  CAUTION!")



            Dim l20 As New SIL3.ApplicationSupport.LabelHelper("Raw Move (um)")
            l20.Layout__BelowControl(btnOn)
            Me.m_txtDevRawMove = New SIL3.ApplicationSupport.TextBoxHelper(100, l20)

            Dim btnMoveLeftDev As New SIL3.ApplicationSupport.ButtonHelper(100, "Move Left", AddressOf btnMoveLeftDev__Click)
            btnMoveLeftDev.Layout__RightOfControl(Me.m_txtDevRawMove)
            Dim btnMoveRightDev As New SIL3.ApplicationSupport.ButtonHelper(100, "Move Right", AddressOf btnMoveRightDev__Click)
            btnMoveRightDev.Layout__RightOfControl(btnMoveLeftDev)
            Dim btnMoveBothDev As New SIL3.ApplicationSupport.ButtonHelper(100, "Move Both", AddressOf btnMoveBothDev__Click)
            btnMoveBothDev.Layout__RightOfControl(btnMoveRightDev)

            Dim l21 As New SIL3.ApplicationSupport.LabelHelper("IBeam Move (mm)")
            l21.Layout__BelowControl(Me.m_txtDevRawMove)
            Me.m_txtDevIBeamMove = New SIL3.ApplicationSupport.TextBoxHelper(100, l21)
            Dim btnMoveIBeam As New SIL3.ApplicationSupport.ButtonHelper(100, "Move", AddressOf btnMoveIBeam__Click)
            btnMoveIBeam.Layout__RightOfControl(Me.m_txtDevIBeamMove)

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

        Private Sub btnDevEnable__Click(s As Object, e As EventArgs)
            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__ENABLE_DEV_MODE,
                                                 &H1293847L, 0, 0, 0)
        End Sub

        Private Sub btnMoveLeftDev__Click(s As Object, e As EventArgs)

            Dim u32Val As New Numerical.U32(CInt(Me.m_txtDevRawMove.Text))

            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__MOVE_MOTOR_RAW,
                                                 0, u32Val.To__Uint32, 0, 0)
        End Sub

        Private Sub btnMoveRightDev__Click(s As Object, e As EventArgs)

            Dim u32Val As New Numerical.U32(CInt(Me.m_txtDevRawMove.Text))

            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__MOVE_MOTOR_RAW,
                                                 1, u32Val.To__Uint32, 0, 0)
        End Sub

        Private Sub btnMoveBothDev__Click(s As Object, e As EventArgs)

            Dim u32Val As New Numerical.U32(CInt(Me.m_txtDevRawMove.Text))

            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__MOVE_MOTOR_RAW,
                                                 2, u32Val.To__Uint32, 0, 0)
        End Sub


        Private Sub btnMoveIBeam__Click(s As Object, e As EventArgs)

            Dim f32Val As New Numerical.F32(CSng(Me.m_txtDevIBeamMove.Text))

            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__MOVE_IBEAM,
                                                 f32Val.Union__Uint32, 0, 0, 0)
        End Sub

        ''' <summary>
        ''' Perform brakes cal
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnCalibrate__Click(s As Object, e As EventArgs)

            If MsgBox("Warning:  Are you sure you want to run cal?", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then

                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__START_CAL_MODE,
                                                 &H112233, 0, 0, 0)

            End If
        End Sub

        Private Sub btnInit__Click(s As Object, e As EventArgs)

            If MsgBox("Warning:  Are you sure you want to Init?", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then

                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__INIT,
                                                 &H98765432L, 0, 0, 0)

            End If
        End Sub

#End Region '#Region "BUTTON HELPERS"

    End Class


End Namespace
