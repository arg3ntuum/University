export const initialState = {
  selectedId: 0,
  messages: {
    0: 'Hello Taylor', // Initial draft for Taylor
    1: 'Hello Alice',  // Initial draft for Alice
    2: 'Hello Bob',    // Initial draft for Bob
  },
};

export function messengerReducer(state, action) {
  switch (action.type) {
    case 'changed_selection': {
      return {
        ...state,
        selectedId: action.contactId,
        // No need to clear the message here; we'll read it from `messages` in App.js.
      };
    }
    case 'edited_message': {
      // 1. Get the draft text from the action.
      const message = action.message;
      // 2. Get the ID of the currently selected contact.
      const id = state.selectedId; 
      return {
        ...state,
        // 3. Update the specific draft for the selected contact ID.
        messages: {
          ...state.messages,
          [id]: message, 
        },
      };
    }
    case 'sent_message': {
      // Get the ID of the currently selected contact.
      const id = state.selectedId; 
      return {
        ...state,
        // Clear the draft for the specific contact ID.
        messages: {
          ...state.messages,
          [id]: '',
        },
      };
    }
    default: {
      throw Error('Unknown action: ' + action.type);
    }
  }
}