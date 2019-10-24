/*******************************************************************************
 * Created Date:      October 23rd, 2019
 * Created By:        Isaac Travers
 * ContextMenu.hpp:   This is a ContextMenu
 *                    it is a vertial menu with highlighting abilities
 *                    when this is displayed, a trie will be traversed
 *                    for all words, those words will be selectable
 *                    by the user. If the user doesn't select any words
 *                    control will be returned to the caller
 *******************************************************************************/

#ifndef CONTEXT_MENU
#define CONTEXT_MENU

#include "EditorMenuPanel.hpp"

namespace TextEditorNamespace {
	class ContextMenu {

	protected:

	public:

		ContextMenu() {

		}

		ContextMenu(WINDOW* parent, Location loc, Size siz)
			//: menu(parent, loc, siz, false, true, false) {
		{

			menu = new EditorMenuPanel(parent, loc, siz, false, true, false);
			
		}

		bool needRefresh() {
			return menu->needsRefresh();
		}

		void render() {
			menu->render();
		}

		void refresh() {
			menu->refresh();
		}

		void toggleVisibility() {
			menu->setIsVisible(!menu->isVisible());
		}

		void addItem(string item,  void (*callBackFunction)(string, void*), void* ptr_to_caller) {
			menu->addItem(item, callBackFunction, ptr_to_caller);
		}

		/*******************************************************************************
		* Function Name:   processMouseEvent(MEVENT* mEvent)
		* Purpose:         Returns vector of all items in the menu.
		*******************************************************************************/
		int processMouseEvent(MEVENT* mEvent) {
			int returnVal = -1;
			if (menu != nullptr) {
				int itemClicked = menu->processMouseEvent(mEvent);
				returnVal = itemClicked;

				if (returnVal != -1) {
					toggleVisibility();
				}
			}
			
			return returnVal;
		}

		//void mainCallback(string menuData, void* this_pointer) {
		//	ContextMenu* self = static_cast<ContextMenu*>(this_pointer);
		//	self->callbackHelper(menuData);
		//}

		//void callbackHelper(string menuData) {
		//	int x = 0;

		//}


	private:
		EditorMenuPanel* menu;// = nullptr;
		//void (*callback)(string, void*);
		//void* callback_pnt_to_caller;

	};	//end class ContextMenu
} //end namespace TextEditorNamespace

#endif