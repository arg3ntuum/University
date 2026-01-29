export default function Letter({
  letter,
  isHighlighted,
  onHover, 
  onToggleStar,
}) {
  return (
    <li
      className={
        isHighlighted ? 'highlighted' : ''
      }
      onFocus={() => {
        onHover();       
      }}
      onPointerMove={() => {
        onHover();
      }}
    >
      <button onClick={() => {
        onToggleStar(letter); 
      }}>
        {letter.isStarred ? 'Unstar' : 'Star'}
      </button>
      {letter.subject}
    </li>
  )
}