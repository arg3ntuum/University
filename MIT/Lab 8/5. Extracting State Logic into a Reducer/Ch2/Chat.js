export default function Chat({contact, message, dispatch}) {
  
  function handleSend() {
    // 1. Показати alert з інформацією
    alert(`Sending "${message}" to ${contact.email}`);
    
    // 2. Диспатчимо дію для очищення поля вводу
    dispatch({
      type: 'sent_message',
    });
  }
  
  return (
    <section className="chat">
      <textarea
        value={message}
        placeholder={'Chat to ' + contact.name}
        onChange={(e) => {
          dispatch({
            type: 'edited_message',
            message: e.target.value,
          });
        }}
      />
      <br />
      {/* */}
      <button onClick={handleSend}>Send to {contact.email}</button>
    </section>
  );
}