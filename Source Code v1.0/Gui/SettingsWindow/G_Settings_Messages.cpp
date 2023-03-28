#include "G_Settings.h"

#include "..\..\Gui\Gui.h"
#include "..\..\Gui\((WindowClasses))\Utility.h"
#include "..\..\Settings\Settings.h"


LRESULT CALLBACK WindowSettings::MessageProcessor(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	LRESULT lResult;
	NMHDR * pNmHdr;
	LPNMLISTVIEW pNmLv;

	switch (uMsg)
	{
		case WM_COMMAND:
		{
			switch (HIWORD(wParam))
			{
				case EN_CHANGE:
				{
					switch (LOWORD(wParam))
					{
						case ID_ED00_START_OUTLINE_INACTIVE + 0:
						case ID_ED00_START_OUTLINE_INACTIVE + 1:
						case ID_ED00_START_OUTLINE_INACTIVE + 2:
						{
							PaintColorBox(Gui::SettWnd.ed00StartOutlineInactive);
							Gui::SettWnd.bt00Save.Enable();
							break;
						}
						case ID_ED00_START_OUTLINE_ACTIVE + 0:
						case ID_ED00_START_OUTLINE_ACTIVE + 1:
						case ID_ED00_START_OUTLINE_ACTIVE + 2:
						{
							PaintColorBox(Gui::SettWnd.ed00StartOutlineActive);
							Gui::SettWnd.bt00Save.Enable();
							break;
						}
						case ID_ED00_START_FILL_INACTIVE + 0:
						case ID_ED00_START_FILL_INACTIVE + 1:
						case ID_ED00_START_FILL_INACTIVE + 2:
						{
							PaintColorBox(Gui::SettWnd.ed00StartFillInactive);
							Gui::SettWnd.bt00Save.Enable();
							break;
						}
						case ID_ED00_START_FILL_ACTIVE + 0:
						case ID_ED00_START_FILL_ACTIVE + 1:
						case ID_ED00_START_FILL_ACTIVE + 2:
						{
							PaintColorBox(Gui::SettWnd.ed00StartFillActive);
							Gui::SettWnd.bt00Save.Enable();
							break;
						}
						case ID_ED00_STOP_OUTLINE_INACTIVE + 0:
						case ID_ED00_STOP_OUTLINE_INACTIVE + 1:
						case ID_ED00_STOP_OUTLINE_INACTIVE + 2:
						{
							PaintColorBox(Gui::SettWnd.ed00StopOutlineInactive);
							Gui::SettWnd.bt00Save.Enable();
							break;
						}
						case ID_ED00_STOP_OUTLINE_ACTIVE + 0:
						case ID_ED00_STOP_OUTLINE_ACTIVE + 1:
						case ID_ED00_STOP_OUTLINE_ACTIVE + 2:
						{
							PaintColorBox(Gui::SettWnd.ed00StopOutlineActive);
							Gui::SettWnd.bt00Save.Enable();
							break;
						}
						case ID_ED00_STOP_FILL_INACTIVE + 0:
						case ID_ED00_STOP_FILL_INACTIVE + 1:
						case ID_ED00_STOP_FILL_INACTIVE + 2:
						{
							PaintColorBox(Gui::SettWnd.ed00StopFillInactive);
							Gui::SettWnd.bt00Save.Enable();
							break;
						}
						case ID_ED00_STOP_FILL_ACTIVE + 0:
						case ID_ED00_STOP_FILL_ACTIVE + 1:
						case ID_ED00_STOP_FILL_ACTIVE + 2:
						{
							PaintColorBox(Gui::SettWnd.ed00StopFillActive);
							Gui::SettWnd.bt00Save.Enable();
							break;
						}
						case ID_ED00_PROGRESSBAR_OUTLINE_INACTIVE + 0:
						case ID_ED00_PROGRESSBAR_OUTLINE_INACTIVE + 1:
						case ID_ED00_PROGRESSBAR_OUTLINE_INACTIVE + 2:
						{
							PaintColorBox(Gui::SettWnd.ed00ProgressBarOutlineInactive);
							Gui::SettWnd.bt00Save.Enable();
							break;
						}
						case ID_ED00_PROGRESSBAR_OUTLINE_ACTIVE + 0:
						case ID_ED00_PROGRESSBAR_OUTLINE_ACTIVE + 1:
						case ID_ED00_PROGRESSBAR_OUTLINE_ACTIVE + 2:
						{
							PaintColorBox(Gui::SettWnd.ed00ProgressBarOutlineActive);
							Gui::SettWnd.bt00Save.Enable();
							break;
						}
						case ID_ED00_PROGRESSBAR_FILL_INACTIVE + 0:
						case ID_ED00_PROGRESSBAR_FILL_INACTIVE + 1:
						case ID_ED00_PROGRESSBAR_FILL_INACTIVE + 2:
						{
							PaintColorBox(Gui::SettWnd.ed00ProgressBarFillInactive);
							Gui::SettWnd.bt00Save.Enable();
							break;
						}
						case ID_ED00_PROGRESSBAR_FILL_ACTIVE_PASSED + 0:
						case ID_ED00_PROGRESSBAR_FILL_ACTIVE_PASSED + 1:
						case ID_ED00_PROGRESSBAR_FILL_ACTIVE_PASSED + 2:
						{
							PaintColorBox(Gui::SettWnd.ed00ProgressBarFillActivePassed);
							Gui::SettWnd.bt00Save.Enable();
							break;
						}
						case ID_ED00_PROGRESSBAR_FILL_ACTIVE_REMAINING + 0:
						case ID_ED00_PROGRESSBAR_FILL_ACTIVE_REMAINING + 1:
						case ID_ED00_PROGRESSBAR_FILL_ACTIVE_REMAINING + 2:
						{
							PaintColorBox(Gui::SettWnd.ed00ProgressBarFillActiveRemaining);
							Gui::SettWnd.bt00Save.Enable();
							break;
						}
					}
					break;
				}
				case LBN_SELCHANGE:
				{
					switch (LOWORD(wParam))
					{
						case ID_LISTBOX:
							Gui::SettWnd.OptionBox_SelectionChanged();
							break;
					}
					break;
				}
				case BN_CLICKED:	
				{
					switch (LOWORD(wParam))
					{
						case ID_BT00_SAVE:
							Gui::SettWnd.SaveButton_Clicked();
							break;
						case ID_RD01_ENGLISH:
							Gui::SettWnd.OnClick_Panel01_Radio_Language(Languages::English);
							break;
						case ID_RD01_TURKISH:
							Gui::SettWnd.OnClick_Panel01_Radio_Language(Languages::Turkish);
							break;
						case ID_RD01_ARABIC:
							Gui::SettWnd.OnClick_Panel01_Radio_Language(Languages::Arabic);
							break;
						case ID_RD01_JAPANESE:
							Gui::SettWnd.OnClick_Panel01_Radio_Language(Languages::Japanese);
							break;
					}
					break;
				}
			}
			break;
		}
		/*case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case ID_LISTBOX:
					if (HIWORD(wParam) == LBN_SELCHANGE)
					{
						Gui::SettWnd.OptionBox_SelectionChanged();
					}
					break;
				default:
					return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;*/
		case WM_DESTROY:
			Gui::SettWnd.Destroy();
			break;
		case WM_NOTIFY:
			pNmHdr = (NMHDR *) lParam;
			/*if (pNmHdr->idFrom == ID_LISTVIEW && pNmHdr->code == LVN_ITEMCHANGED)
			{
			pNmLv = (LPNMLISTVIEW) lParam;
			if ((pNmLv->uChanged   & LVIF_STATE) && (pNmLv->uNewState & LVIS_SELECTED) != (pNmLv->uOldState & LVIS_SELECTED))
			{
			Gui::SettWnd.SttsBar.SetPartText(2, pNmLv->iItem);
			if (pNmLv->uNewState & LVIS_SELECTED)
			{
			Gui::SettWnd.SttsBar.SetPartText(3, L"Selected");
			}
			else
			{
			Gui::SettWnd.SttsBar.SetPartText(3, L"Unselected");
			}
			}
			}*/
			break;
		case WM_MOVE:
			RECT Rect;
			GetWindowRect(hWnd, &Rect);
			Settings::SettingsWindow::SettWnd_X = Rect.left;
			Settings::SettingsWindow::SettWnd_Y = Rect.top;
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WindowSettings::ChildWindowProc(	HWND		hWnd,
													UINT		uMsg,
													WPARAM		wParam,
													LPARAM		lParam,
													UINT_PTR	uIdSubclass,
													DWORD_PTR	dwRefData)
{
	switch (uMsg)
	{
		case WM_NOTIFY:
			::SendMessageW(Gui::SettWnd.Window.hWnd, uMsg, wParam, lParam);
			break;
		case WM_PAINT:
		{
			LRESULT lResult = DefSubclassProc(hWnd, uMsg, wParam, lParam);
			switch (uIdSubclass)
			{
				case ID_ED00_START_OUTLINE_INACTIVE:
				{
					PaintColorBox(Gui::SettWnd.ed00StartOutlineInactive);
					break;
				}
				case ID_ED00_START_OUTLINE_ACTIVE:
				{
					PaintColorBox(Gui::SettWnd.ed00StartOutlineActive);
					break;
				}
				case ID_ED00_START_FILL_INACTIVE:
				{
					PaintColorBox(Gui::SettWnd.ed00StartFillInactive);
					break;
				}
				case ID_ED00_START_FILL_ACTIVE:
				{
					PaintColorBox(Gui::SettWnd.ed00StartFillActive);
					break;
				}
				case ID_ED00_STOP_OUTLINE_INACTIVE:
				{
					PaintColorBox(Gui::SettWnd.ed00StopOutlineInactive);
					break;
				}
				case ID_ED00_STOP_OUTLINE_ACTIVE:
				{
					PaintColorBox(Gui::SettWnd.ed00StopOutlineActive);
					break;
				}
				case ID_ED00_STOP_FILL_INACTIVE:
				{
					PaintColorBox(Gui::SettWnd.ed00StopFillInactive);
					break;
				}
				case ID_ED00_STOP_FILL_ACTIVE:
				{
					PaintColorBox(Gui::SettWnd.ed00StopFillActive);
					break;
				}
				case ID_ED00_PROGRESSBAR_OUTLINE_INACTIVE:
				{
					PaintColorBox(Gui::SettWnd.ed00ProgressBarOutlineInactive);
					break;
				}
				case ID_ED00_PROGRESSBAR_OUTLINE_ACTIVE:
				{
					PaintColorBox(Gui::SettWnd.ed00ProgressBarOutlineActive);
					break;
				}
				case ID_ED00_PROGRESSBAR_FILL_INACTIVE:
				{
					PaintColorBox(Gui::SettWnd.ed00ProgressBarFillInactive);
					break;
				}
				case ID_ED00_PROGRESSBAR_FILL_ACTIVE_PASSED:
				{
					PaintColorBox(Gui::SettWnd.ed00ProgressBarFillActivePassed);
					break;
				}
				case ID_ED00_PROGRESSBAR_FILL_ACTIVE_REMAINING:
				{
					PaintColorBox(Gui::SettWnd.ed00ProgressBarFillActiveRemaining);
					break;
				}
			}
			return lResult;
			break;
		}
		default:
			return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}
