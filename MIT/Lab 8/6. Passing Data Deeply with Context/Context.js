// Context.js
import { createContext, useContext } from 'react';

// Create a context for the image size value.
export const ImageSizeContext = createContext(100);

// Optional: Custom hook for cleaner consumption
export function useImageSize() {
  return useContext(ImageSizeContext);
}