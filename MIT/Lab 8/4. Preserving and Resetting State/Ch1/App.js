import { useState } from 'react';

export default function App() {
  const [showHint, setShowHint] = useState(false);
  
  return (
    <div>
      {/* 1. Conditionally render the hint message above the Form. */}
      {showHint &&
        <p><i>Hint: Your favorite city?</i></p>
      }
      
      {/* 2. Keep the Form component in the same, consistent location. */}
      <Form />
      
      {/* 3. Conditionally render the Hide/Show button. */}
      {showHint ? (
        <button onClick={() => {
          setShowHint(false);
        }}>Hide hint</button>
      ) : (
        <button onClick={() => {
          setShowHint(true);
        }}>Show hint</button>
      )}
    </div>
  );
}

function Form() {
  const [text, setText] = useState('');
  return (
    <textarea
      value={text}
      onChange={e => setText(e.target.value)}
    />
  );
}