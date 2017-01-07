Namespace SIL3.rLoop.rPodControl.Panels.FlightControl

    ''' <summary>
    ''' SpaceX required packet
    ''' </summary>
    ''' <remarks></remarks>
    Public Class SpaceX
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"
#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        Private m_iRxCount As Integer
        Private m_txtCount As SIL3.ApplicationSupport.TextBoxHelper

        ''' <summary>
        ''' The logging directory
        ''' </summary>
        Private m_sLogDir As String

        ''' <summary>
        ''' Allows us to write CSV logs of the edges
        ''' </summary>
        Private m_pCSV As SIL3.FileSupport.CSV


        Private m_txtTeamID As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtStatus As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtAccel As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtPosition As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtVelocity As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtBattVoltage As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtBattCurrent As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtBattTemp As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtPodTemp As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtStripeCount As SIL3.ApplicationSupport.TextBoxHelper


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
            Me.m_sLogDir = Me.m_sLogDir & "SPACEX\"

            'check our folder
            SIL3.FileSupport.FileHelpers.Folder__CheckWarnMake(Me.m_sLogDir)

            'create the log files in prep
            Me.m_pCSV = New SIL3.FileSupport.CSV(Me.m_sLogDir & "telemetry.csv", ",", False, False)
            If Me.m_pCSV.File__Exists = False Then
            End If

        End Sub
#End Region '#Region "NEW"

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
        ''' Rx a normal packet
        ''' </summary>
        ''' <param name="u8Array"></param>
        ''' <param name="iLength"></param>
        Public Sub InternalEvent__RxPacketA(u8Array() As Byte, iLength As Integer)
            'spacex packet

            If MyBase.m_bLayout = True Then
                'UDP is 42 bytes in
                Dim iIndex As Integer = 42

                Dim u8TeamID As New Numerical.U8(u8Array, iIndex)
                iIndex += 1

                Dim u8Status As New Numerical.U8(u8Array, iIndex)
                iIndex += 1

                Dim s32Accel As New Numerical.S32(u8Array, iIndex)
                iIndex += 4

                Dim s32Pos As New Numerical.S32(u8Array, iIndex)
                iIndex += 4

                Dim s32Veloc As New Numerical.S32(u8Array, iIndex)
                iIndex += 4

                Dim s32BattV As New Numerical.S32(u8Array, iIndex)
                iIndex += 4

                Dim s32BattI As New Numerical.S32(u8Array, iIndex)
                iIndex += 4

                Dim s32BattTemp As New Numerical.S32(u8Array, iIndex)
                iIndex += 4

                Dim s32PodTemp As New Numerical.S32(u8Array, iIndex)
                iIndex += 4

                Dim u32StripeCount As New Numerical.U32(u8Array, iIndex)
                iIndex += 4


                'update the GUI
                Me.m_txtTeamID.Threadsafe__SetText(u8TeamID.To_String)
                Me.m_txtStatus.Threadsafe__SetText(u8Status.To_String)
                Me.m_txtAccel.Threadsafe__SetText(s32Accel.To__Int.ToString)
                Me.m_txtPosition.Threadsafe__SetText(s32Pos.To__Int.ToString)
                Me.m_txtVelocity.Threadsafe__SetText(s32Veloc.To__Int.ToString)
                Me.m_txtBattVoltage.Threadsafe__SetText(s32BattV.To__Int.ToString)
                Me.m_txtBattCurrent.Threadsafe__SetText(s32BattI.To__Int.ToString)
                Me.m_txtBattTemp.Threadsafe__SetText(s32BattTemp.To__Int.ToString)
                Me.m_txtPodTemp.Threadsafe__SetText(s32PodTemp.To__Int.ToString)
                Me.m_txtStripeCount.Threadsafe__SetText(u32StripeCount.To__Uint32.ToString)

                'update the rx packet count
                Me.m_iRxCount += 1
                Me.m_txtCount.Threadsafe__SetText(Me.m_iRxCount.ToString)

            End If


        End Sub


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


            End If

        End Sub


#End Region '#Region "EVENTS"

#Region "PANEL LAYOUT"
        ''' <summary>
        ''' Create our layout prior to being shown
        ''' </summary>
        ''' <remarks></remarks>
        Public Overrides Sub LayoutPanel()

            Dim l0 As New SIL3.ApplicationSupport.LabelHelper(10, 10, "Team ID", MyBase.m_pInnerPanel)
            Me.m_txtTeamID = New SIL3.ApplicationSupport.TextBoxHelper(100, l0)

            Dim l1 As New SIL3.ApplicationSupport.LabelHelper("Pod Status")
            l1.Layout__AboveRightControl(l0, Me.m_txtTeamID)
            Me.m_txtStatus = New SIL3.ApplicationSupport.TextBoxHelper(100, l1)

            Dim l2 As New SIL3.ApplicationSupport.LabelHelper("Acceleration cm/s²")
            l2.Layout__BelowControl(m_txtTeamID)
            Me.m_txtAccel = New SIL3.ApplicationSupport.TextBoxHelper(100, l2)

            Dim l3 As New SIL3.ApplicationSupport.LabelHelper("Postion cm")
            l3.Layout__AboveRightControl(l2, Me.m_txtAccel)
            Me.m_txtPosition = New SIL3.ApplicationSupport.TextBoxHelper(100, l3)

            Dim l4 As New SIL3.ApplicationSupport.LabelHelper("Velocity cm/s")
            l4.Layout__AboveRightControl(l3, Me.m_txtPosition)
            Me.m_txtVelocity = New SIL3.ApplicationSupport.TextBoxHelper(100, l4)

            Dim l5 As New SIL3.ApplicationSupport.LabelHelper("Batt Voltage mV")
            l5.Layout__BelowControl(Me.m_txtAccel)
            Me.m_txtBattVoltage = New SIL3.ApplicationSupport.TextBoxHelper(100, l5)

            Dim l6 As New SIL3.ApplicationSupport.LabelHelper("Batt Current mA")
            l6.Layout__AboveRightControl(l5, Me.m_txtBattVoltage)
            Me.m_txtBattCurrent = New SIL3.ApplicationSupport.TextBoxHelper(100, l6)

            Dim l7 As New SIL3.ApplicationSupport.LabelHelper("Batt Temp 0.1C")
            l7.Layout__AboveRightControl(l6, Me.m_txtBattCurrent)
            Me.m_txtBattTemp = New SIL3.ApplicationSupport.TextBoxHelper(100, l7)

            Dim l8 As New SIL3.ApplicationSupport.LabelHelper("Pod Temp 0.1C")
            l8.Layout__BelowControl(Me.m_txtBattVoltage)
            Me.m_txtPodTemp = New SIL3.ApplicationSupport.TextBoxHelper(100, l8)

            Dim l9 As New SIL3.ApplicationSupport.LabelHelper("Stripe Count")
            l9.Layout__AboveRightControl(l8, Me.m_txtPodTemp)
            Me.m_txtStripeCount = New SIL3.ApplicationSupport.TextBoxHelper(100, l9)


            Dim l11 As New SIL3.ApplicationSupport.LabelHelper("Rx Count")
            l11.Layout__BelowControl(Me.m_txtPodTemp)
            Me.m_txtCount = New SIL3.ApplicationSupport.TextBoxHelper(100, l11)

        End Sub

#End Region '#Region "PANEL LAYOUT"


    End Class


End Namespace
