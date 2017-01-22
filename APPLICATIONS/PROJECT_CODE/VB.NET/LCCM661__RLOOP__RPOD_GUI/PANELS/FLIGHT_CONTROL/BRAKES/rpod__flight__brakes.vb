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

        Private m_txtFlags(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper_FaultFlags
        Private m_txtSpares(C_NUM_BRAKES - 1, 5 - 1) As SIL3.ApplicationSupport.TextBoxHelper

        Private m_txtTargetIBeam(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtTargetScrew_mm(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtTargetScrew_um(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper_U32

        Private m_txtCurrentIBeam(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtCurrentScrew_mm(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtCurrentMLP_mm(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper_F32


        'switches
        Private m_txtLimitsExtend_State(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper_StateDisplay
        Private m_txtLimitsRetract_State(C_NUM_BRAKES - 1) As SIL3.ApplicationSupport.TextBoxHelper_StateDisplay
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


        Private m_txtBrakeState As SIL3.ApplicationSupport.TextBoxHelper_StateDisplay
        Private m_txtBrakeCalState As SIL3.ApplicationSupport.TextBoxHelper_StateDisplay

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
            Me.m_sLogDir = Me.m_sLogDir & "BRAKES\"

            'check our folder
            SIL3.FileSupport.FileHelpers.Folder__CheckWarnMake(Me.m_sLogDir, True)

            'create the log files in prep
            'Me.m_pCSV = New SIL3.FileSupport.CSV(Me.m_sLogDir & "Laser0.csv", ",", False, False)
            'If Me.m_pCSV.File__Exists = False Then
            'End If

            Me.m_pDAQ = New SIL3.DAQ.Top()

            'add the contrast DAQ items
            Me.m_pDAQ.DAQ__Set_LogFilePath(Me.m_sLogDir)

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

                    Dim pU32Spare(C_NUM_BRAKES - 1, 2 - 1) As SIL3.Numerical.U32


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
                    Dim pu8BrakeCalState As SIL3.Numerical.U8

                    For iCounter As Integer = 0 To C_NUM_BRAKES - 1

                        iOffset += Me.m_txtFlags(iCounter).Flags__Update(u8Payload, iOffset, True)
                        'targets
                        iOffset += Me.m_txtTargetIBeam(iCounter).Value__Update(u8Payload, iOffset)
                        iOffset += Me.m_txtTargetScrew_mm(iCounter).Value__Update(u8Payload, iOffset)
                        iOffset += Me.m_txtTargetScrew_um(iCounter).Value__Update(u8Payload, iOffset)

                        'current pos
                        iOffset += Me.m_txtCurrentIBeam(iCounter).Value__Update(u8Payload, iOffset)
                        iOffset += Me.m_txtCurrentScrew_mm(iCounter).Value__Update(u8Payload, iOffset)
                        iOffset += Me.m_txtCurrentMLP_mm(iCounter).Value__Update(u8Payload, iOffset)

                        'spares
                        iOffset += 8


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
                    pu8BrakeCalState = New SIL3.Numerical.U8(u8Payload, iOffset)
                    iOffset += 1


                    'update the GUI
                    For iCounter As Integer = 0 To C_NUM_BRAKES - 1



                        'Me.m_txtSpares(iCounter, 3).Threadsafe__SetText(pU32Spare(iCounter, 3).To_String)
                        'Me.m_txtSpares(iCounter, 4).Threadsafe__SetText(pU32Spare(iCounter, 4).To_String)

                        Me.m_txtLimitsExtend_State(iCounter).Value__Update(pu8LimitsExtend_State(iCounter).To__Int)
                        Me.m_txtLimitsRetract_State(iCounter).Value__Update(pu8LimitsRetract_State(iCounter).To__Int)
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
                    Me.m_txtBrakeState.Value__Update(pu8BrakeState.To__Int)
                    Me.m_txtBrakeCalState.Value__Update(pu8BrakeCalState.To__Int)

                    Me.m_iRxCount += 1
                    Me.m_txtCount.Threadsafe__SetText(Me.m_iRxCount.ToString)

                ElseIf ePacketType >= SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_DAQ__OFFSET_INDEX And ePacketType <= SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_DAQ__OFFSET_INDEX + 128 Then

                    'DAQ packet
                    'Pass off to the DAQ system
                    Me.m_pDAQ.InernalEvent__UDPSafe__RxPacket(SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_DAQ__OFFSET_INDEX,
                                                              ePacketType, u16PayloadLength, u8Payload, u16CRC, True, 0)

                    Me.m_iRxCount += 1
                    Me.m_txtCount.Threadsafe__SetText(Me.m_iRxCount.ToString)

                End If
            End If

        End Sub





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
            Dim iIndex As Integer = 0

            'general
            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper(10, 10, "Fault Flags " & Me.Layout__GetBrakeSide(iDevice), MyBase.m_pInnerPanel)
            Me.m_txtFlags(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Target IBeam " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtFlags(iDevice))
            Me.m_txtTargetIBeam(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_F32(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Target Screw (mm) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtTargetIBeam(iDevice))
            Me.m_txtTargetScrew_mm(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_F32(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Target Screw (um) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtTargetScrew_mm(iDevice))
            Me.m_txtTargetScrew_um(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_U32(100, l0(iDevice, iIndex))
            iIndex += 1

            'current
            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Curr. IBeam (mm) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__BelowControl(Me.m_txtFlags(iDevice))
            Me.m_txtCurrentIBeam(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_F32(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Curr. Screw (mm) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtCurrentIBeam(iDevice))
            Me.m_txtCurrentScrew_mm(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_F32(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Curr. MLP (mm) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtCurrentScrew_mm(iDevice))
            Me.m_txtCurrentMLP_mm(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_F32(100, l0(iDevice, iIndex))
            iIndex += 1


            'switches
            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Sw Ext State " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__BelowControl(Me.m_txtCurrentIBeam(iDevice))
            Me.m_txtLimitsExtend_State(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_StateDisplay(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Sw Retract State " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtLimitsExtend_State(iDevice))
            Me.m_txtLimitsRetract_State(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_StateDisplay(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Sw Ext Edge " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__BelowControl(Me.m_txtLimitsExtend_State(iDevice))
            Me.m_txtLimitsExtend_EdgeSeen(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Sw Retract Edge " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtLimitsExtend_EdgeSeen(iDevice))
            Me.m_txtLimitsRetract_EdgeSeen(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            'mlp
            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("MLP ADC " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__BelowControl(Me.m_txtLimitsExtend_EdgeSeen(iDevice))
            Me.m_txtMLP_ADC(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("MLP ADC Zero " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtMLP_ADC(iDevice))
            Me.m_txtMLP_ADCZero(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("MLP ADC Span " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtMLP_ADCZero(iDevice))
            Me.m_txtMLP_ADCSpan(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("MLP Position(mm) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtMLP_ADCSpan(iDevice))
            Me.m_txtMLP_Position_mm(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            'stepper
            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Stepper Veloc " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Location = New System.Drawing.Point(Me.m_txtMLP_ADC(iDevice).Location.X, Me.m_txtMLP_ADC(iDevice).Location.Y + Me.m_txtMLP_ADC(iDevice).Size.Height + 50)
            Me.m_pInnerPanel.Controls.Add(l0(iDevice, iIndex))
            'l0(iDevice, 12).Layout__BelowControl(Me.m_txtMLP_ADC(iDevice))
            Me.m_txtStep_Veloc(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Stepper Accel " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtStep_Veloc(iDevice))
            Me.m_txtStep_Accel(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Stepper Pos " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtStep_Accel(iDevice))
            Me.m_txtStep_CurrentPos(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1




            iDevice = 1
            iIndex = 0
            'general
            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Fault Flags " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice - 1, 0), Me.m_txtTargetScrew_um(iDevice - 1))
            Me.m_txtFlags(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Target IBeam " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtFlags(iDevice))
            Me.m_txtTargetIBeam(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_F32(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Target Screw (mm) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtTargetIBeam(iDevice))
            Me.m_txtTargetScrew_mm(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_F32(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Target Screw (um) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtTargetScrew_mm(iDevice))
            Me.m_txtTargetScrew_um(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_U32(100, l0(iDevice, iIndex))
            iIndex += 1

            'current
            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Curr. IBeam (mm) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__BelowControl(Me.m_txtFlags(iDevice))
            Me.m_txtCurrentIBeam(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_F32(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Curr. Screw (mm) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtCurrentIBeam(iDevice))
            Me.m_txtCurrentScrew_mm(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_F32(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Curr. MLP (mm) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtCurrentScrew_mm(iDevice))
            Me.m_txtCurrentMLP_mm(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_F32(100, l0(iDevice, iIndex))
            iIndex += 1

            'switches
            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Sw Ext State " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__BelowControl(Me.m_txtCurrentIBeam(iDevice))
            Me.m_txtLimitsExtend_State(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_StateDisplay(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Sw Retract State " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtLimitsExtend_State(iDevice))
            Me.m_txtLimitsRetract_State(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper_StateDisplay(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Sw Ext Edge " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__BelowControl(Me.m_txtLimitsExtend_State(iDevice))
            Me.m_txtLimitsExtend_EdgeSeen(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Sw Retract Edge " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtLimitsExtend_EdgeSeen(iDevice))
            Me.m_txtLimitsRetract_EdgeSeen(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            'mlp
            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("MLP ADC " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__BelowControl(Me.m_txtLimitsExtend_EdgeSeen(iDevice))
            Me.m_txtMLP_ADC(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("MLP ADC Zero " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtMLP_ADC(iDevice))
            Me.m_txtMLP_ADCZero(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("MLP ADC Span " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtMLP_ADCZero(iDevice))
            Me.m_txtMLP_ADCSpan(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("MLP Position(mm) " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtMLP_ADCSpan(iDevice))
            Me.m_txtMLP_Position_mm(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            'stepper
            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Stepper Veloc " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Location = New System.Drawing.Point(Me.m_txtMLP_ADC(iDevice).Location.X, Me.m_txtMLP_ADC(iDevice).Location.Y + Me.m_txtMLP_ADC(iDevice).Size.Height + 50)
            Me.m_pInnerPanel.Controls.Add(l0(iDevice, iIndex))
            'l0(iDevice, 12).Layout__BelowControl(Me.m_txtMLP_ADC(iDevice))
            Me.m_txtStep_Veloc(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Stepper Accel " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtStep_Veloc(iDevice))
            Me.m_txtStep_Accel(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            l0(iDevice, iIndex) = New SIL3.ApplicationSupport.LabelHelper("Stepper Pos " & Me.Layout__GetBrakeSide(iDevice))
            l0(iDevice, iIndex).Layout__AboveRightControl(l0(iDevice, iIndex - 1), Me.m_txtStep_Accel(iDevice))
            Me.m_txtStep_CurrentPos(iDevice) = New SIL3.ApplicationSupport.TextBoxHelper(100, l0(iDevice, iIndex))
            iIndex += 1

            Dim l10 As New SIL3.ApplicationSupport.LabelHelper("Brakes State")
            l10.Layout__BelowControl(Me.m_txtStep_Veloc(0))
            Me.m_txtBrakeState = New SIL3.ApplicationSupport.TextBoxHelper_StateDisplay(200, l10)
            Dim l100 As New SIL3.ApplicationSupport.LabelHelper("Calibration State")
            l100.Layout__AboveRightControl(l10, Me.m_txtBrakeState)
            Me.m_txtBrakeCalState = New SIL3.ApplicationSupport.TextBoxHelper_StateDisplay(200, l100)


            Me.m_txtBrakeState.States__Add("BRAKE_STATE__RESET")
            Me.m_txtBrakeState.States__Add("BRAKE_STATE__IDLE")
            Me.m_txtBrakeState.States__Add("BRAKE_STATE__BEGIN_MOVE")
            Me.m_txtBrakeState.States__Add("BRAKE_STATE__COMPUTE")
            Me.m_txtBrakeState.States__Add("BRAKE_STATE__MOVING")
            Me.m_txtBrakeState.States__Add("BRAKE_STATE__MOVE_STOPPED")
            Me.m_txtBrakeState.States__Add("BRAKE_STATE__FAULT")
            Me.m_txtBrakeState.States__Add("BRAKE_STATE__TEST")
            Me.m_txtBrakeState.States__Add("BRAKE_STATE__BEGIN_CAL")
            Me.m_txtBrakeState.States__Add("BRAKE_STATE__WAIT_CAL_DONE")


            Me.m_txtBrakeCalState.States__Add("BRAKE_CAL_STATE__IDLE")
            Me.m_txtBrakeCalState.States__Add("BRAKE_CAL_STATE__EXTEND_MOTORS")
            Me.m_txtBrakeCalState.States__Add("BRAKE_CAL_STATE__WAIT_EXTEND_MOTORS")
            Me.m_txtBrakeCalState.States__Add("BRAKE_CAL_STATE__RELEASE_ZERO")
            Me.m_txtBrakeCalState.States__Add("BRAKE_CAL_STATE__APPLY_NEW_ZERO")
            Me.m_txtBrakeCalState.States__Add("BRAKE_CAL_STATE__WAIT_NEW_ZERO")
            Me.m_txtBrakeCalState.States__Add("BRAKE_CAL_STATE__COMPLETE")

            For iCounter As Integer = 0 To C_NUM_BRAKES - 1
                Me.m_txtLimitsExtend_State(iCounter).States__Add("UNKNOWN")
                Me.m_txtLimitsExtend_State(iCounter).States__Add("CLOSED")
                Me.m_txtLimitsExtend_State(iCounter).States__Add("OPEN")
                Me.m_txtLimitsRetract_State(iCounter).States__Add("UNKNOWN")
                Me.m_txtLimitsRetract_State(iCounter).States__Add("CLOSED")
                Me.m_txtLimitsRetract_State(iCounter).States__Add("OPEN")
            Next


            Dim l11 As New SIL3.ApplicationSupport.LabelHelper("Rx Count")
            l11.Layout__BelowControl(Me.m_txtBrakeState)
            Me.m_txtCount = New SIL3.ApplicationSupport.TextBoxHelper(100, l11)

            Dim btnOn As New SIL3.ApplicationSupport.ButtonHelper(100, "Stream On", AddressOf btnStreamOn__Click)
            btnOn.Layout__RightOfControl(Me.m_txtCount)

            Dim btnDAQ As New SIL3.ApplicationSupport.ButtonHelper(100, "Enable DAQ", AddressOf btnDAQ__Click)
            btnDAQ.Layout__RightOfControl(btnOn)

            Dim btnInit As New SIL3.ApplicationSupport.ButtonHelper(100, "Init Brakes", AddressOf btnInit__Click)
            btnInit.Layout__BelowControl(Me.m_txtCount)
            btnInit.ToolTip__Set("Brake Init", "This is required after reset")


            Dim btnDevEnable As New SIL3.ApplicationSupport.ButtonHelper(100, "Dev Enable", AddressOf btnDevEnable__Click)
            btnDevEnable.Layout__BelowControl(btnInit)
            btnDevEnable.ToolTip__Set("Development Enable", "Use this to enable development mode before any manual brake commands can be sent.")

            Dim btnCal As New SIL3.ApplicationSupport.ButtonHelper(100, "Calibrate", AddressOf btnCalibrate__Click)
            btnCal.Layout__RightOfControl(btnDevEnable)
            btnCal.ToolTip__Set("Calibration", "Calibrate the brakes (Only works in DEV mode)  CAUTION!")



            Dim l20 As New SIL3.ApplicationSupport.LabelHelper("Raw Move (um)")
            l20.Layout__BelowControl(btnDevEnable)
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


            'add the MLP buttons
            'Me.m_txtMLP_ADCZero(iDevice)
            Dim btnMLP_L_Zero As New SIL3.ApplicationSupport.ButtonHelper(100, "ADC Zero", AddressOf Me.btnMLP_L_ZERO__Click)
            btnMLP_L_Zero.Layout__BelowControl(Me.m_txtMLP_ADCZero(0))
            Dim btnMLP_R_Zero As New SIL3.ApplicationSupport.ButtonHelper(100, "ADC Zero", AddressOf Me.btnMLP_R_ZERO__Click)
            btnMLP_R_Zero.Layout__BelowControl(Me.m_txtMLP_ADCZero(1))

            Dim btnMLP_L_Span As New SIL3.ApplicationSupport.ButtonHelper(100, "ADC Span", AddressOf Me.btnMLP_L_SPAN__Click)
            btnMLP_L_Span.Layout__RightOfControl(btnMLP_L_Zero)
            Dim btnMLP_R_Span As New SIL3.ApplicationSupport.ButtonHelper(100, "ADC Span", AddressOf Me.btnMLP_R_SPAN__Click)
            btnMLP_R_Span.Layout__RightOfControl(btnMLP_R_Zero)


            For iDevice = 0 To C_NUM_BRAKES - 1
                Me.m_txtFlags(iDevice).Flags__Add("GENERAL")
                Me.m_txtFlags(iDevice).Flags__Add("MLP_RANGE_LIMIT_LOW")
                Me.m_txtFlags(iDevice).Flags__Add("MLP_RANGE_LIMIT_HIGH")
                Me.m_txtFlags(iDevice).Flags__Add("CALIBRATION DATA RELOAD")
                Me.m_txtFlags(iDevice).Flags__Add("DEVELOPMENT MODE ENABLE")
                Me.m_txtFlags(iDevice).Flags__Add("")
                Me.m_txtFlags(iDevice).Flags__Add("")
                Me.m_txtFlags(iDevice).Flags__Add("")
                Me.m_txtFlags(iDevice).Flags__Add("")
                Me.m_txtFlags(iDevice).Flags__Add("")
                Me.m_txtFlags(iDevice).Flags__Add("")
                Me.m_txtFlags(iDevice).Flags__Add("")
                Me.m_txtFlags(iDevice).Flags__Add("")

            Next

        End Sub

#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        ''' <summary>
        ''' Enable streaming
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnStreamOn__Click(s As Object, e As EventArgs)

            Dim pSB As SIL3.ApplicationSupport.ButtonHelper = CType(s, SIL3.ApplicationSupport.ButtonHelper)

            If pSB.Text = "Stream On" Then
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 1, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__TX_DATA, 0, 0)

                pSB.Text = "Stream Off"
            Else

                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 0, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__TX_DATA, 0, 0)
                pSB.Text = "Stream On"
            End If


        End Sub

        ''' <summary>
        ''' Enable DAQ
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnDAQ__Click(s As Object, e As EventArgs)


            Dim pSB As SIL3.ApplicationSupport.ButtonHelper = CType(s, SIL3.ApplicationSupport.ButtonHelper)

            If pSB.Text = "Enable DAQ" Then

                'clear any types
                Me.m_pDAQ.DAQTypes__Clear()

                'configure the DAQ
                Me.m_pDAQ.DAQTypes__Register(0, 0, 0, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__U8, "CPU Load", 100)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 1, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__S32, "LEFT_POS", 100)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 2, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__S32, "RIGHT_POS", 100)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 1, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__U32, "LEFT_TARGET", 100)
                Me.m_pDAQ.DAQTypes__Register(0, 0, 2, DAQ.Top.E_DAQ__DATA_TYPES.DATA_TYPE__U32, "RIGHT_TARGET", 100)

                'switch on the DAQ
                Me.m_pDAQ.DAQ__Start(False)

                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__DAQ_ENABLE,
                                                 1, 0, 0, 0)

                pSB.Text = "Disable DAQ"
            Else
                'stopping will also flush
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__DAQ_ENABLE,
                                                 0, 0, 0, 0)


                'the DAQ will be flished here.

                pSB.Text = "Enable DAQ"
            End If


        End Sub

        ''' <summary>
        ''' Enable development mode
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
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


        Private Sub btnMLP_L_ZERO__Click(s As Object, e As EventArgs)

            If MsgBox("Warning: Really zero LEFT MLP ADC?", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then

                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__MLP_ZEROSPAN,
                                                 &H55660123L, 0, 0, 0)

            End If
        End Sub

        Private Sub btnMLP_R_ZERO__Click(s As Object, e As EventArgs)

            If MsgBox("Warning: Really zero RIGHT MLP ADC?", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then

                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__MLP_ZEROSPAN,
                                                 &H55660123L, 1, 0, 0)

            End If
        End Sub

        Private Sub btnMLP_L_SPAN__Click(s As Object, e As EventArgs)

            If MsgBox("Warning: Really Span LEFT MLP ADC?", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then

                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__MLP_ZEROSPAN,
                                                 &H55660123L, 0, 1, 0)

            End If
        End Sub

        Private Sub btnMLP_R_SPAN__Click(s As Object, e As EventArgs)

            If MsgBox("Warning: Really Span RIGHT MLP ADC?", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then

                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_BRAKES__MLP_ZEROSPAN,
                                                 &H55660123L, 1, 1, 0)

            End If
        End Sub

#End Region '#Region "BUTTON HELPERS"

    End Class


End Namespace
