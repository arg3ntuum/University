import { useState } from 'react';

export default function App() {
  const [reverse, setReverse] = useState(false);
  
  // Define the Field components with unique, consistent keys.
  const firstNameField = <Field key="first" label="First name" />;
  const lastNameField = <Field key="last" label="Last name" />;

  let checkbox = (
    <label>
      <input
        type="checkbox"
        checked={reverse}
        onChange={e => setReverse(e.target.checked)}
      />
      Reverse order
    </label>
  );

  // Determine the order of fields based on the state
  let fields;
  if (reverse) {
    // Reversed: [Last Name, First Name]
    fields = (
      <>
        {lastNameField}
        {firstNameField}
      </>
    );
  } else {
    // Default: [First Name, Last Name]
    fields = (
      <>
        {firstNameField}
        {lastNameField}
      </>
    );
  }

  return (
    <>
      {fields}
      {checkbox}
    </>
  );
}

function Field({ label }) {
  const [text, setText] = useState('');
  return (
    <label>
      {label}:{' '}
      <input
        type="text"
        value={text}
        placeholder={label}
        onChange={e => setText(e.target.value)}
      />
    </label>
  );
}