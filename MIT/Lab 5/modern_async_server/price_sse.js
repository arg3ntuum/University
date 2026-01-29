const priceDiv = document.getElementById('btcPrice');
const es = new EventSource('/price-stream');

es.onmessage = (e) => {
  try {
    const obj = JSON.parse(e.data);
    if (obj.usd != null) priceDiv.textContent = `USD: ${obj.usd}`;
    else if (obj.error) priceDiv.textContent = `Error: ${obj.error}`;
  } catch (err) {
    priceDiv.textContent = 'Parse error';
    console.error('SSE parse', err);
  }
};

es.onerror = (err) => {
  console.error('SSE error', err);
  priceDiv.textContent = 'SSE error / disconnected';
};
