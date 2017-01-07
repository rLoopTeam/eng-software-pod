Namespace SIL3.Airsanz.DataLogger

    ''' <summary>
    ''' Top level for data logging application
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Top

#Region "MEMBERS"

        Private m_pIONormal As SIL3.ApplicationSupport.IOData_Visualise

        ''' <summary>
        ''' The tray status strip
        ''' </summary>
        ''' <remarks></remarks>
        Private m_pSS As SIL3.ApplicationSupport.StatusStripHelper

        ''' <summary>
        ''' The USB interface
        ''' </summary>
        ''' <remarks></remarks>
        Private m_pUSB As SIL3.Airsanz.DataLogger.USBInterface

        ''' <summary>
        ''' Has new data arrived?
        ''' </summary>
        ''' <remarks></remarks>
        Private m_bNewData As Boolean

        Private m_sLastSlots As String

        Private m_pGBNormal As GroupBox
        Private m_pGBStats As GroupBox

        ''' <summary>
        ''' The ethernet interface
        ''' </summary>
        Private m_pEth As SIL3.Airsanz.DataLogger.EthInterface

        ''' <summary>
        ''' Number of units to log for
        ''' </summary>
        Private m_txtNumUnits As SIL3.ApplicationSupport.TextBoxHelper

        Private m_txtLogDir As SIL3.ApplicationSupport.TextBoxHelper

        Private m_pSG As SIL3.ApplicationSupport.SandGrid.Grid

#End Region '#Region "MEMBERS"

#Region "NEW"

        Public Sub New(ByRef pF As Windows.Forms.Form)

            'create the form
            Me.LayoutForm(pF)

            Me.m_pUSB = New SIL3.Airsanz.DataLogger.USBInterface()

            'start the eth
            Me.m_pEth = New SIL3.Airsanz.DataLogger.EthInterface(CInt(Me.m_txtNumUnits.Text))

            AddHandler Me.m_pUSB.New__TagData, AddressOf Me.New__TagData
            AddHandler Me.m_pUSB.New__TagState, AddressOf Me.New__TagState
            AddHandler Me.m_pUSB.New__TagHours, AddressOf Me.New__TagHours
            AddHandler Me.m_pUSB.New__TagLife, AddressOf Me.New__TagLife
            AddHandler Me.m_pUSB.New__Data, AddressOf Me.New__Data
            AddHandler Me.m_pUSB.New__LastSlot, AddressOf Me.New__LastSlot


            AddHandler Me.m_pUSB.DeviceConnected, AddressOf Me.InternalEvent__USBToolbox__DeviceConnected
            AddHandler Me.m_pUSB.DeviceDisconnected, AddressOf Me.InternalEvent__USBToolbox__DeviceDisconnected
            AddHandler Me.m_pUSB.DeviceFound, AddressOf Me.InternalEvent__USBToolbox__DeviceFound



        End Sub

        ''' <summary>
        ''' Close our application
        ''' </summary>
        ''' <remarks></remarks>
        Public Sub Destroy()
            Me.m_pUSB.Destory()
            Me.m_pEth.destroy
        End Sub

#End Region '#Region "NEW"

#Region "HELPERS"
        ''' <summary>
        ''' Convert a tag state to a string
        ''' </summary>
        ''' <param name="eState"></param>
        ''' <returns></returns>
        ''' <remarks></remarks>
        Private Function TagState__ToString(eState As Airsanz.DataLogger.USBInterface.AIRSANZ_RFID__TAG_STATES_E)

            Select Case eState
                Case USBInterface.AIRSANZ_RFID__TAG_STATES_E.TAG_STATE__UNKNOWN
                    Return "UNKNOWN"
                Case USBInterface.AIRSANZ_RFID__TAG_STATES_E.TAG_STATE__NEVER_USED
                    Return "NEVER USED"
                Case USBInterface.AIRSANZ_RFID__TAG_STATES_E.TAG_STATE__MISSING
                    Return "MISSING"
                Case USBInterface.AIRSANZ_RFID__TAG_STATES_E.TAG_STATE__IN_USE_LOW
                    Return "LOW"
                Case USBInterface.AIRSANZ_RFID__TAG_STATES_E.TAG_STATE__IN_USE
                    Return "IN USE"
                Case USBInterface.AIRSANZ_RFID__TAG_STATES_E.TAG_STATE__EXPIRED
                    Return "EXPIRED"
                Case Else
                    Return "ERROR"
            End Select

        End Function
#End Region

#Region "FORM LAYOUT"

        Private Sub PanelClick(sender As Object, e As EventArgs)

            Dim pP As SIL3.ApplicationSupport.StatusStripHelper = CType(sender, SIL3.ApplicationSupport.StatusStripHelper)


        End Sub

        ''' <summary>
        ''' Create the form
        ''' </summary>
        ''' <remarks></remarks>
        Private Sub LayoutForm(ByRef pF As Windows.Forms.Form)

            'setup the form
            pF.WindowState = FormWindowState.Maximized
            pF.Text = "Airsanz - Data Logger (Build: " & My.Application.Info.Version.ToString & ")"

            Me.m_pSS = New SIL3.ApplicationSupport.StatusStripHelper(pF)
            Me.m_pSS.Panel__Add("USB Device:")
            Me.m_pSS.Panel__Add("USB Tx/Rx:")
            Me.m_pSS.Panel__Add("Stats")
            AddHandler Me.m_pSS.PanelClick, AddressOf Me.PanelClick

            'create our inner pannel
            Dim pP As New SIL3.ApplicationSupport.PanelHelper(pF, ApplicationSupport.Themes.eTheme.THEME__LIGHT)

            'create the controls
            Dim l1 As New SIL3.ApplicationSupport.LabelHelper(10, 10, "Number of Units (restart required)", pP)
            Me.m_txtNumUnits = New SIL3.ApplicationSupport.TextBoxHelper(100, l1)
            Me.m_txtNumUnits.Persist__Set(Types.eLockieCompanyType.SIL3__APP_PATH, "num_units.txt")
            AddHandler Me.m_txtNumUnits.KeyDown, AddressOf Me.txtNumUnits__KeyDown
            If Me.m_txtNumUnits.Text = "" Then
                Me.m_txtNumUnits.Threadsafe__SetText("1")
                Me.m_txtNumUnits.Persist__Save()
            End If

            Dim l2 As New SIL3.ApplicationSupport.LabelHelper("Controls", Me.m_txtNumUnits)
            Dim btnStart As New SIL3.ApplicationSupport.ButtonHelper(100, "Start", Nothing)
            btnStart.Layout__BelowControl(l2)

            'setup the logging directory
            Dim l3 As New SIL3.ApplicationSupport.LabelHelper("Logging Directory", btnStart)
            Me.m_txtLogDir = New SIL3.ApplicationSupport.TextBoxHelper(500, l3)
            Me.m_txtLogDir.Persist__Set(Types.eLockieCompanyType.SIL3__APP_PATH, "logging_directory.txt")

            Dim btnChooseLog As New SIL3.ApplicationSupport.ButtonHelper(100, "...", AddressOf Me.btnChooseLogDir__CLick)
            btnChooseLog.Layout__RightOfControl(Me.m_txtLogDir)

            'layout the unique devices
            Dim pP2 As New Panel
            With pP2
                .Dock = DockStyle.Bottom
                .Size = New Size(100, 500)
                .BackColor = Color.Blue

            End With
            pP.Controls.Add(pP2)

            Me.m_pSG = New SIL3.ApplicationSupport.SandGrid.Grid(pP2, False)
            Me.m_pSG.Column__Add("\",
                                 New String() {"IP Address"},
                                 New String() {""},
                                 New Integer() {180},
                                 New Boolean() {False},
                                 New SIL3.ApplicationSupport.SandGrid.Grid.eCellTypes() {SIL3.ApplicationSupport.SandGrid.Grid.eCellTypes.TEXT})


            Return


            Me.m_pGBNormal = New GroupBox
            With Me.m_pGBNormal
                .Dock = DockStyle.Fill
                .BackColor = Color.White
            End With
            pF.Controls.Add(Me.m_pGBNormal)

            Me.m_pGBStats = New GroupBox
            With Me.m_pGBStats
                .Dock = DockStyle.Fill
                .BackColor = Color.White
                .Visible = False
            End With
            pF.Controls.Add(Me.m_pGBStats)


            Me.m_pIONormal = New SIL3.ApplicationSupport.IOData_Visualise(Me.m_pGBNormal)
            AddHandler Me.m_pIONormal.ButtonClick, AddressOf Me.IO_ButtonClick


            With Me.m_pIONormal
                Dim iCol As Integer = .Column_Add("A", "Controls", 0, 0)
                .Button_Add(iCol, ApplicationSupport.IOData_Visualise._eIDOV_ButtonTypes.BUTTON_TYPE_PUSH, "kRequest", "Request New Data", False)

                iCol = .Column_Add("B", "Fragrance RFID", 2, 0)
                .Box_Add(iCol, ApplicationSupport.IOData_Visualise._eIDOV_BoxTypes.BOX_TYPE_VARIABLE_VALUE, "RFID0_TAG_ID", "", False, "RFID Tag ID")
                .Box_Add(iCol, ApplicationSupport.IOData_Visualise._eIDOV_BoxTypes.BOX_TYPE_VARIABLE_VALUE, "RFID0_TAG_STATE", "", False, "Tag State")
                .Box_Add(iCol, ApplicationSupport.IOData_Visualise._eIDOV_BoxTypes.BOX_TYPE_VARIABLE_VALUE, "RFID0_TAG_HOURS", "", False, "Hours Elapsed")


                iCol = .Column_Add("C", "Sprayer RFID", 2, 1)
                .Box_Add(iCol, ApplicationSupport.IOData_Visualise._eIDOV_BoxTypes.BOX_TYPE_VARIABLE_VALUE, "RFID1_TAG_ID", "", False, "RFID Tag ID")
                .Box_Add(iCol, ApplicationSupport.IOData_Visualise._eIDOV_BoxTypes.BOX_TYPE_VARIABLE_VALUE, "RFID1_TAG_STATE", "", False, "Tag State")
                .Box_Add(iCol, ApplicationSupport.IOData_Visualise._eIDOV_BoxTypes.BOX_TYPE_VARIABLE_VALUE, "RFID1_TAG_HOURS", "", False, "Sprays Consumed")

                iCol = .Column_Add("D", "AMF RFID", 2, 2)
                .Box_Add(iCol, ApplicationSupport.IOData_Visualise._eIDOV_BoxTypes.BOX_TYPE_VARIABLE_VALUE, "RFID2_TAG_ID", "", False, "RFID Tag ID")
                .Box_Add(iCol, ApplicationSupport.IOData_Visualise._eIDOV_BoxTypes.BOX_TYPE_VARIABLE_VALUE, "RFID2_TAG_STATE", "", False, "Tag State")
                .Box_Add(iCol, ApplicationSupport.IOData_Visualise._eIDOV_BoxTypes.BOX_TYPE_VARIABLE_VALUE, "RFID2_TAG_HOURS", "", False, "Hours Elapsed")


                iCol = .Column_Add("E", "Fragrance Special Controls", 6, 0)
                .Box_Add(iCol, ApplicationSupport.IOData_Visualise._eIDOV_BoxTypes.BOX_COMBO_SELECT, "RFID0_TAG_LIFE", "", False, "RFID Tag Life")
                .Box_Combo__AddItem(iCol, 0, "6 Months")
                .Box_Combo__AddItem(iCol, 0, "6 Weeks")
                .Box_Combo__AddItem(iCol, 0, "6 Days")
                .Box_Combo__AddItem(iCol, 0, "6 Hours")

                iCol = .Column_Add("F", "Sprayer Special Controls", 6, 1)
                .Box_Add(iCol, ApplicationSupport.IOData_Visualise._eIDOV_BoxTypes.BOX_COMBO_SELECT, "RFID1_TAG_LIFE", "", False, "RFID Tag Life")
                .Box_Combo__AddItem(iCol, 0, "6 Months")
                .Box_Combo__AddItem(iCol, 0, "6 Weeks")
                .Box_Combo__AddItem(iCol, 0, "6 Days")
                .Box_Combo__AddItem(iCol, 0, "6 Hours")

                iCol = .Column_Add("F", "AMF Special Controls", 6, 2)
                .Box_Add(iCol, ApplicationSupport.IOData_Visualise._eIDOV_BoxTypes.BOX_COMBO_SELECT, "RFID2_TAG_LIFE", "", False, "RFID Tag Life")
                .Box_Combo__AddItem(iCol, 0, "6 Months")
                .Box_Combo__AddItem(iCol, 0, "6 Weeks")
                .Box_Combo__AddItem(iCol, 0, "6 Days")
                .Box_Combo__AddItem(iCol, 0, "6 Hours")

                iCol = .Column_Add("F", "Recent Tag List", 8, 0)
                .Box_Add(iCol, ApplicationSupport.IOData_Visualise._eIDOV_BoxTypes.BOX_MULTILINE_TEXT, "TAG_LIST", "", False, "RFID Tag List", 3)


                iCol = .Column_Add("A", "Special Functions", 12, 0)
                .Button_Add(iCol, ApplicationSupport.IOData_Visualise._eIDOV_ButtonTypes.BUTTON_TYPE_PUSH, "kReset", "Reset All Data", False)


            End With

            AddHandler Me.m_pIONormal.ComboBox__SelectedIndexChanged, AddressOf Me.ComboBox__SelectedIndexChanged

        End Sub

#End Region '#Region "FORM LAYOUT"

#Region "KEY PRESS"
        Private Sub txtNumUnits__KeyDown(s As Object, e As KeyEventArgs)
            If e.KeyCode = Keys.Enter Then
                Me.m_txtNumUnits.Persist__Save()
                MsgBox("Restart the application now")
            End If
        End Sub
#End Region

#Region "BUTTON HANDLERS"

        ''' <summary>
        ''' Choose and save the log file directory.
        ''' </summary>
        ''' <param name="sender"></param>
        ''' <param name="e"></param>
        Private Sub btnChooseLogDir__CLick(sender As Object, e As EventArgs)

            Dim pC As New SIL3.FileSupport.FileDialogHelpers.FolderChoose()
            Dim sR As String = pC.ShowDialog
            If sR <> "" Then
                Me.m_txtLogDir.Threadsafe__SetText(sR)
                Me.m_txtLogDir.Persist__Save()
            End If

        End Sub

        ''' <summary>
        ''' Handle the expiry tag life
        ''' </summary>
        ''' <param name="sTag"></param>
        ''' <param name="sNewValue"></param>
        ''' <remarks></remarks>
        Private Sub ComboBox__SelectedIndexChanged(sTag As String, sNewValue As String)


            If MsgBox("Are you sure you want to change the tag life to " & sNewValue & "?", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then
                Select Case sTag
                    Case "RFID0_TAG_LIFE"

                        Select Case sNewValue
                            Case "6 Months"
                                Me.m_pUSB.Tx__SetRIFD_TagLife(0, 6 * 24 * 30)
                            Case "6 Weeks"
                                Me.m_pUSB.Tx__SetRIFD_TagLife(0, 6 * 24 * 7)
                            Case "6 Days"
                                Me.m_pUSB.Tx__SetRIFD_TagLife(0, 6 * 24)
                            Case "6 Hours"
                                Me.m_pUSB.Tx__SetRIFD_TagLife(0, 6)
                        End Select

                    Case "RFID1_TAG_LIFE"
                        Select Case sNewValue
                            Case "6 Months"
                                Me.m_pUSB.Tx__SetRIFD_TagLife(1, 6 * 24 * 30)
                            Case "6 Weeks"
                                Me.m_pUSB.Tx__SetRIFD_TagLife(1, 6 * 24 * 7)
                            Case "6 Days"
                                Me.m_pUSB.Tx__SetRIFD_TagLife(1, 6 * 24)
                            Case "6 Hours"
                                Me.m_pUSB.Tx__SetRIFD_TagLife(1, 6)
                        End Select

                    Case "RFID2_TAG_LIFE"
                        Select Case sNewValue
                            Case "6 Months"
                                Me.m_pUSB.Tx__SetRIFD_TagLife(2, 6 * 24 * 30)
                            Case "6 Weeks"
                                Me.m_pUSB.Tx__SetRIFD_TagLife(2, 6 * 24 * 7)
                            Case "6 Days"
                                Me.m_pUSB.Tx__SetRIFD_TagLife(2, 6 * 24)
                            Case "6 Hours"
                                Me.m_pUSB.Tx__SetRIFD_TagLife(2, 6)
                        End Select
                End Select

            End If

        End Sub


        ''' <summary>
        ''' Wait for a transmission before going again
        ''' </summary>
        ''' <remarks></remarks>
        Private Sub Wait__TxComplete()
            Do
                Application.DoEvents()
                System.Threading.Thread.Sleep(10)
            Loop While Me.m_bNewData = False

            System.Threading.Thread.Sleep(50)

        End Sub


        Private Sub Request_All()
            Dim iDelay As Integer = 150

            'clear prior to the request
            Me.m_pIONormal.Box_SetValue("RFID0_TAG_ID", "")
            Me.m_pIONormal.Box_SetValue("RFID1_TAG_ID", "")
            Me.m_pIONormal.Box_SetValue("RFID2_TAG_ID", "")

            Me.m_pIONormal.Box_SetValue("RFID0_TAG_STATE", "")
            Me.m_pIONormal.Box_SetValue("RFID1_TAG_STATE", "")
            Me.m_pIONormal.Box_SetValue("RFID2_TAG_STATE", "")


            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_TagHeader(0)
            Me.Wait__TxComplete()

            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_TagID(0)
            Me.Wait__TxComplete()

            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_TagHeader(1)
            Me.Wait__TxComplete()

            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_TagID(1)
            Me.Wait__TxComplete()

            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_TagHeader(2)
            Me.Wait__TxComplete()

            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_TagID(2)
            Me.Wait__TxComplete()


            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_TagState(0)
            Me.Wait__TxComplete()

            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_TagState(1)
            Me.Wait__TxComplete()

            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_TagState(2)
            Me.Wait__TxComplete()



            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_TagHours(0)
            Me.Wait__TxComplete()

            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_TagHours(1)
            Me.Wait__TxComplete()

            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_TagHours(2)
            Me.Wait__TxComplete()


            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_TagLife(0)
            Me.Wait__TxComplete()

            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_TagLife(1)
            Me.Wait__TxComplete()

            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_TagLife(2)
            Me.Wait__TxComplete()

            Me.m_sLastSlots = ""
            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_LastEntry(0)
            Me.Wait__TxComplete()
            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_LastEntry(1)
            Me.Wait__TxComplete()
            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_LastEntry(2)
            Me.Wait__TxComplete()
            Me.m_bNewData = False
            Me.m_pUSB.Tx__RequestRIFD_LastEntry(3)
            Me.Wait__TxComplete()
        End Sub

        ''' <summary>
        ''' Handles the IO button click.
        ''' </summary>
        ''' <param name="sButtonKey"></param>
        ''' <param name="bIsOn"></param>
        ''' <remarks></remarks>
        Private Sub IO_ButtonClick(ByVal sButtonKey As String, ByVal bIsOn As Boolean)

            Select Case sButtonKey

                Case "kReset"
                    If MsgBox("CAUTION!. Do you want to reset all the data on the board?", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then
                        Me.m_pUSB.Tx__ResetAll()

                        MsgBox("Board Reset, you must request all data again")

                    End If


                Case "kRequest"

                    Me.Request_All()

            End Select

        End Sub

#End Region '#Region "BUTTON HANDLERS"

#Region "USB INTERFACE"

        ''' <summary>
        ''' Called when the device has been disconnected.
        ''' </summary>
        ''' <param name="sDeviceName"></param>
        ''' <remarks></remarks>
        Private Sub InternalEvent__USBToolbox__DeviceConnected(ByVal sDeviceName As String)

            If Not Me.m_pSS Is Nothing Then
                Me.m_pSS.Panel__SetText(0, "USB Device: " & sDeviceName)
            End If

        End Sub

        ''' <summary>
        ''' USB toolbox signalling device disconnected
        ''' </summary>
        ''' <remarks></remarks>
        Private Sub InternalEvent__USBToolbox__DeviceDisconnected()

            If Not Me.m_pSS Is Nothing Then
                Me.m_pSS.Panel__SetText(0, "USB Device: Not Connected")
            End If

        End Sub

        ''' <summary>
        ''' USB toolbox signalling device has been found via
        ''' the find timer.
        ''' </summary>
        ''' <param name="sDeviceName"></param>
        ''' <remarks></remarks>
        Private Sub InternalEvent__USBToolbox__DeviceFound(ByVal sDeviceName As String)

            If Not Me.m_pSS Is Nothing Then
                Me.m_pSS.Panel__SetText(0, "USB Device: " & sDeviceName)
            End If

        End Sub

        ''' <summary>
        ''' New data tag has arrived based on our request
        ''' </summary>
        ''' <param name="iTagIndex"></param>
        ''' <param name="u8Header"></param>
        ''' <param name="u32ID"></param>
        ''' <remarks></remarks>
        Private Sub New__TagData(iTagIndex As Integer, u8Header As Numerical.U8, u32ID As Numerical.U32)

            Select Case iTagIndex
                Case 0
                    Dim sText As String = u8Header.To_String & u32ID.To_String(True)
                    Me.m_pIONormal.Box_SetValue("RFID0_TAG_ID", sText)
                Case 1
                    Dim sText As String = u8Header.To_String & u32ID.To_String(True)
                    Me.m_pIONormal.Box_SetValue("RFID1_TAG_ID", sText)
                Case 2
                    Dim sText As String = u8Header.To_String & u32ID.To_String(True)
                    Me.m_pIONormal.Box_SetValue("RFID2_TAG_ID", sText)

            End Select

        End Sub

        ''' <summary>
        ''' Update the state of the tag
        ''' </summary>
        ''' <param name="iTagIndex"></param>
        ''' <param name="eState"></param>
        ''' <remarks></remarks>
        Private Sub New__TagState(iTagIndex As Integer, eState As Airsanz.DataLogger.USBInterface.AIRSANZ_RFID__TAG_STATES_E)
            Select Case iTagIndex
                Case 0
                    Me.m_pIONormal.Box_SetValue("RFID0_TAG_STATE", Me.TagState__ToString(eState))
                Case 1
                    Me.m_pIONormal.Box_SetValue("RFID1_TAG_STATE", Me.TagState__ToString(eState))
                Case 2
                    Me.m_pIONormal.Box_SetValue("RFID2_TAG_STATE", Me.TagState__ToString(eState))
            End Select
        End Sub

        ''' <summary>
        ''' Update the number of hours the tag has been in use for
        ''' </summary>
        ''' <param name="iTagIndex"></param>
        ''' <param name="u16Hours"></param>
        ''' <remarks></remarks>
        Private Sub New__TagHours(iTagIndex As Integer, u16Hours As Numerical.U16)
            Select Case iTagIndex
                Case 0
                    Me.m_pIONormal.Box_SetValue("RFID0_TAG_HOURS", u16Hours.To__Uint32.To__Int.ToString)
                Case 1
                    Me.m_pIONormal.Box_SetValue("RFID1_TAG_HOURS", u16Hours.To__Uint32.To__Int.ToString)
                Case 2
                    Me.m_pIONormal.Box_SetValue("RFID2_TAG_HOURS", u16Hours.To__Uint32.To__Int.ToString)
            End Select
        End Sub

        ''' <summary>
        ''' Update the list of last slots
        ''' </summary>
        ''' <param name="iSlotIndex"></param>
        ''' <param name="u32"></param>
        ''' <remarks></remarks>
        Private Sub New__LastSlot(iSlotIndex As Integer, u32 As Numerical.U32)
            Select Case iSlotIndex
                Case 0
                    Me.m_sLastSlots = u32.To_String & Environment.NewLine
                Case 1
                    Me.m_sLastSlots = Me.m_sLastSlots & u32.To_String & Environment.NewLine
                Case 2
                    Me.m_sLastSlots = Me.m_sLastSlots & u32.To_String & Environment.NewLine
                Case 3
                    Me.m_sLastSlots = Me.m_sLastSlots & u32.To_String & Environment.NewLine
                    Me.m_pIONormal.Box_SetValue("TAG_LIST", Me.m_sLastSlots)
            End Select
        End Sub

        ''' <summary>
        ''' Update the tag life combo
        ''' </summary>
        ''' <param name="iTagIndex"></param>
        ''' <param name="u16Hours"></param>
        ''' <remarks></remarks>
        Private Sub New__TagLife(iTagIndex As Integer, u16Hours As Numerical.U16)
            Select Case iTagIndex
                Case 0
                    RemoveHandler Me.m_pIONormal.ComboBox__SelectedIndexChanged, AddressOf Me.ComboBox__SelectedIndexChanged
                    Dim iVal As Integer = u16Hours.To__Uint32.To__Int
                    Select Case iVal
                        Case 6
                            '6hr
                            Me.m_pIONormal.Box_Combo__SetIndex(4, 0, 3)
                        Case 6 * 24
                            '6day
                            Me.m_pIONormal.Box_Combo__SetIndex(4, 0, 2)
                        Case 6 * 24 * 7
                            '6 weeks
                            Me.m_pIONormal.Box_Combo__SetIndex(4, 0, 1)
                        Case 6 * 24 * 30
                            '6 months
                            Me.m_pIONormal.Box_Combo__SetIndex(4, 0, 0)
                        Case Else
                            Me.m_pIONormal.Box_Combo__SetIndex(4, 0, 3)

                    End Select
                    AddHandler Me.m_pIONormal.ComboBox__SelectedIndexChanged, AddressOf Me.ComboBox__SelectedIndexChanged
                Case 1
                    RemoveHandler Me.m_pIONormal.ComboBox__SelectedIndexChanged, AddressOf Me.ComboBox__SelectedIndexChanged
                    Select Case u16Hours.To__Uint32.To__Int
                        Case 6
                            '6hr
                            Me.m_pIONormal.Box_Combo__SetIndex(5, 0, 3)
                        Case 6 * 24
                            '6day
                            Me.m_pIONormal.Box_Combo__SetIndex(5, 0, 2)
                        Case 6 * 24 * 7
                            '6 weeks
                            Me.m_pIONormal.Box_Combo__SetIndex(5, 0, 1)
                        Case 6 * 24 * 30
                            '6 months
                            Me.m_pIONormal.Box_Combo__SetIndex(5, 0, 0)
                        Case Else
                            Me.m_pIONormal.Box_Combo__SetIndex(5, 0, 3)

                    End Select
                    AddHandler Me.m_pIONormal.ComboBox__SelectedIndexChanged, AddressOf Me.ComboBox__SelectedIndexChanged

                Case 2
                    RemoveHandler Me.m_pIONormal.ComboBox__SelectedIndexChanged, AddressOf Me.ComboBox__SelectedIndexChanged
                    Select Case u16Hours.To__Uint32.To__Int
                        Case 6
                            '6hr
                            Me.m_pIONormal.Box_Combo__SetIndex(6, 0, 3)
                        Case 6 * 24
                            '6day
                            Me.m_pIONormal.Box_Combo__SetIndex(6, 0, 2)
                        Case 6 * 24 * 7
                            '6 weeks
                            Me.m_pIONormal.Box_Combo__SetIndex(6, 0, 1)
                        Case 6 * 24 * 30
                            '6 months
                            Me.m_pIONormal.Box_Combo__SetIndex(6, 0, 0)
                        Case Else
                            Me.m_pIONormal.Box_Combo__SetIndex(6, 0, 3)

                    End Select
                    AddHandler Me.m_pIONormal.ComboBox__SelectedIndexChanged, AddressOf Me.ComboBox__SelectedIndexChanged

            End Select
        End Sub


        Private Sub New__Data()
            Me.m_bNewData = True
        End Sub

#End Region '#Region "USB INTERFACE"

    End Class
End Namespace