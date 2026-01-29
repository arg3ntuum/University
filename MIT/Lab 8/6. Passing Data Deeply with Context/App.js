import { useState, useContext } from 'react';
import { places } from './data.js';
import { getImageUrl } from './utils.js';
import { ImageSizeContext } from './Context.js';

// FIX: Using const declaration for helper components to ensure proper scope definition.

// PlaceImage no longer takes imageSize prop
const PlaceImage = ({ place }) => { 
  // Consume the context directly to get the imageSize
  const imageSize = useContext(ImageSizeContext);
  
  return (
    <img
      src={getImageUrl(place)}
      alt={place.name}
      width={imageSize}
      height={imageSize}
    />
  );
}

// Place no longer takes imageSize prop
const Place = ({ place }) => { 
  return (
    <>
      {/* No imageSize prop passed */}
      <PlaceImage place={place} />
      <p>
        <b>{place.name}</b>
        {': ' + place.description}
      </p>
    </>
  );
}

//  List no longer takes imageSize prop
const List = () => { 
  const listItems = places.map(place =>
    <li key={place.id}>
      {/*  No imageSize prop passed */}
      <Place place={place} />
    </li>
  );
  return <ul>{listItems}</ul>;
}


export default function App() {
  const [isLarge, setIsLarge] = useState(false);
  const imageSize = isLarge ? 150 : 100;
  
  return (
    // Wrap the entire tree in the Provider
    <ImageSizeContext.Provider value={imageSize}>
      <label>
        <input
          type="checkbox"
          checked={isLarge}
          onChange={e => {
            setIsLarge(e.target.checked);
          }}
        />
        Use large images
      </label>
      <hr />
      {/* List is now correctly defined and in scope */}
      <List /> 
    </ImageSizeContext.Provider>
  )
}