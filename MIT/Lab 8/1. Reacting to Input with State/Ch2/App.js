import { useState } from 'react';

export default function EditProfile() {
  // 1. State for controlling the form mode (View or Edit)
  const [isEditing, setIsEditing] = useState(false);
  
  // 2. States for controlling the user data
  const [firstName, setFirstName] = useState('Jane');
  const [lastName, setLastName] = useState('Jacobs');

  // Helper function to handle the form submission (Edit/Save button click)
  function handleFormSubmit(e) {
    // Prevent the default form submission behavior (page reload)
    e.preventDefault();
    
    // Toggle the editing mode
    setIsEditing(!isEditing);
    
    // NOTE: In the original JS, the button text was changed here.
    // In React, the button text is determined by the `isEditing` state in the JSX below.
  }

  // Helper function to handle changes in the input fields
  function handleFirstNameChange(e) {
    // Update the firstName state
    setFirstName(e.target.value);
  }

  function handleLastNameChange(e) {
    // Update the lastName state
    setLastName(e.target.value);
  }

  // Determine the display logic
  const buttonText = isEditing ? 'Save Profile' : 'Edit Profile';

  return (
    <form onSubmit={handleFormSubmit}>
      <label>
        First name:{' '}
        {/* Conditional rendering: show input if editing, otherwise show text */}
        {isEditing ? (
          <input 
            value={firstName} 
            onChange={handleFirstNameChange} 
          />
        ) : (
          <b>{firstName}</b>
        )}
      </label>
      
      <label>
        Last name:{' '}
        {/* Conditional rendering: show input if editing, otherwise show text */}
        {isEditing ? (
          <input 
            value={lastName} 
            onChange={handleLastNameChange} 
          />
        ) : (
          <b>{lastName}</b>
        )}
      </label>
      
      {/* The button's text and submit action are handled here */}
      <button type="submit">
        {buttonText}
      </button>
      
      {/* The welcome message always updates based on the current state values */}
      <p><i>Hello, {firstName} {lastName}!</i></p>
    </form>
  );
}