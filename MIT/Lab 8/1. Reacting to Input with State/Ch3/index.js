// --- STATE ---
// The single source of truth for the application
let firstName = 'Jane';
let lastName = 'Jacobs';
let isEditing = false;

// --- STATE SETTERS (They update the state AND call updateDOM) ---

function setFirstName(value) {
  firstName = value;
  updateDOM();
}

function setLastName(value) {
  lastName = value;
  updateDOM();
}

function setIsEditing(value) {
  isEditing = value;
  updateDOM();
}

// --- CORE DECLARATIVE FUNCTION ---
// Renders the UI based ONLY on the current state.
function updateDOM() {
  // 1. Update the button text based on the mode
  // 2. Conditionally show/hide elements based on the mode
  if (isEditing) {
    editButton.textContent = 'Save Profile';
    
    // Show inputs, hide text content
    hide(firstNameText);
    hide(lastNameText);
    show(firstNameInput);
    show(lastNameInput);
    
    // Set input values from state (necessary when entering edit mode)
    firstNameInput.value = firstName;
    lastNameInput.value = lastName;
  } else {
    editButton.textContent = 'Edit Profile';
    
    // Hide inputs, show text content
    hide(firstNameInput);
    hide(lastNameInput);
    show(firstNameText);
    show(lastNameText);
    
    // Set text content from state
    firstNameText.textContent = firstName;
    lastNameText.textContent = lastName;
  }
  
  // 3. Update the 'Hello' text (always based on current state)
  helloText.textContent = (
    'Hello, ' +
    firstName + ' ' + // Use state variable here!
    lastName + '!'    // Use state variable here!
  );
}

// --- EVENT HANDLERS (Update state only) ---

function handleFormSubmit(e) {
  e.preventDefault();
  // Toggle isEditing state
  setIsEditing(!isEditing);
}

function handleFirstNameChange(e) {
  // Update firstName state
  setFirstName(e.target.value);
}

function handleLastNameChange(e) {
  // Update lastName state
  setLastName(e.target.value);
}

// --- UTILITY FUNCTIONS ---

function hide(el) {
  el.style.display = 'none';
}

function show(el) {
  el.style.display = '';
}

// --- INITIALIZATION CODE ---
let form = document.getElementById('form');
let editButton = document.getElementById('editButton');
let firstNameInput = document.getElementById('firstNameInput');
let firstNameText = document.getElementById('firstNameText');
let lastNameInput = document.getElementById('lastNameInput');
let lastNameText = document.getElementById('lastNameText');
let helloText = document.getElementById('helloText');

form.onsubmit = handleFormSubmit;
firstNameInput.oninput = handleFirstNameChange;
lastNameInput.oninput = handleLastNameChange;

updateDOM();