const endpoint = "http://192.168.198.186";
const ledMapping = {
  dapur: {
    button: ledDapur,
    image: dapurLedImage,
  },
  makan: {
    button: ledMakan,
    image: makanLedImage,
  },
  tamu: {
    button: ledTamu,
    image: tamuLedImage,
  },
  toilet: {
    button: ledToilet,
    image: toiletLedImage,
  },
};

// Function to fetch LED state
function getLedState(room) {
  fetch(`${endpoint}/${room}`, { method: "GET" })
    .then((response) => response.text())
    .then((result) => {
      const { button, image } = ledMapping[room];
      if (result === "ON") {
        button.style.backgroundColor = "blue";
        image.src = "./Komponen/led-on.png";
      } else {
        button.style.backgroundColor = "#579fff";
        image.src = "./Komponen/led-off.png";
      }
    })
    .catch((error) => console.error(`Error fetching ${room} LED state:`, error));
}

// Function to toggle LED state
function toggleLedState(room) {
  fetch(`${endpoint}/${room}`, { method: "POST" })
    .then((response) => response.text())
    .then(() => getLedState(room)) // Refresh the LED state without reloading
    .catch((error) => console.error(`Error toggling ${room} LED state:`, error));
}

// Initialize all LED states
Object.keys(ledMapping).forEach(getLedState);

// Example button click handlers
ledDapur.addEventListener("click", () => toggleLedState("dapur"));
ledMakan.addEventListener("click", () => toggleLedState("makan"));
ledTamu.addEventListener("click", () => toggleLedState("tamu"));
ledToilet.addEventListener("click", () => toggleLedState("toilet"));
