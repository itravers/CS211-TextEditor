#/********************************************************************************
 *	Isaac Travers
 *	CIS 211 - Data Structures
 *	October 11th, 2019
 *
 *	MenuBehaviour.hpp: Encapsulates the behaviour of a menu
 *                     This is using the strategy class
 *                     Each menu has a menu behaviour, the behaviour decides
 *                     how the menu will be rendered. Each behaviour can
 *                     render the menu in a different way.
*********************************************************************************/

#ifndef MENU_BEHAVIOUR_HPP
#define MENU_BEHAVIOUR_HPP

#include "EditorWindowMoveable.hpp"
//#include "EditorMenu.hpp"


//we are defining a class in the namespace TextEditorNamespace
namespace TextEditorNamespace {
	
	//forward declare editorMenu
	//class EditorMenu;

	//we are defining a MenuBehaviour
	class MenuBehaviour {

		//We'll be extending this class later, these will be private for extended classes
	protected:
		//EditorMenu* parent;
		vector<string>& _parent_buffer;

		/*******************************************************************************
			* Function Name:   imprintStringOnBuffer(s1, int y, int x)
			* Purpose:         Imprints string s1 onto string onto the buffer
			*                  at the given y and x value
			*******************************************************************************/
		void imprintStringOnBuffer(string s1, int y, int x = 0) {

			//We only imprint a string into the buffer for a line that exists in the buffer
			

			if (y < _parent_buffer.size()) {
				string oldString = _parent_buffer[y];
				string newString = imprintString(s1, oldString, x);
				_parent_buffer[y] = newString;
			}

		}

		/*******************************************************************************
			* Function Name:   imprintString(s1, s2)
			* Purpose:         Imprints string s1 onto string s2
			*                  If s1 is larger than s2, we will chop s1 down
			*                  until it is the size of s2, then s2 = s1.
			*                  Otherwise s2 is larger than s1, and we pad
			*                  s1 so it is the size of s2, then we s2 = s1;
			*******************************************************************************/
		string imprintString(string s1, string s2, int startX = 0) {
			if (s1.size() == s2.size()) {

				//everything is good, just replace the string.
				s2 = s1;
			}
			else if (s1.size() < s2.size()) {

				//we need to pad s1, until it is the size of s2, before we replace
				int diff = s2.size() - s1.size();
				s1.insert(s1.length(), diff, ' ');		//padding happens here
				s2 = s1;

			}
			else {

				//we need to chop s1, so it is only the size of s2, before we replace
				int length = s2.size();		//the length we need our string to be chopped to
				s1 = (s1.substr(startX));
				s2 = s1;
			}

			//if startX is not zero, it means we are shifting the string, but we don't want to resize the string at all
			int size = s2.size();					//record size
			if (startX >= s2.length()) {
				s2 = "";
				//s2.insert(s2.length(), size, ' ');
			}
			else {
				s2 = s2.substr(startX);					//take subtring starting at startX
			}

			int diff = size - s2.size();			//calculate difference from new string size to target string size
			s2.insert(s2.length(), diff, ' ');		//pad the string so it is the proper size.

			return s2;
		}


		//These will be public for all extended classes
	public:

		//constructor
		MenuBehaviour(vector<string>&_buf) 
		  :_parent_buffer(_buf){
		//MenuBehaviour(EditorMenu* p) {
		//	parent = p;
			
			
		}

		/*******************************************************************************
		* Function Name:   render()
		* Purpose:         Extending classes will need to implement their own render
		*******************************************************************************/
		virtual void render(vector<string>items) = 0;

		//These will not be available to extended classes, or anyone else.
	private:

	}; // end class MenuBehaviour
} // end TextEditorNamespace

#endif