// Add this code to your existing script.js or in the section where you initialize Mapbox

// Access token from Mapbox (Replace with your own access token)
mapboxgl.accessToken = 'pk.eyJ1IjoiYXNtYWltcmFuIiwiYSI6ImNtNHk5cWFweDBwcjYya3M3eWJkM3lhZDQifQ.lCDZVmQ9uPd80NkIqLitYw';

// Initialize the map
const map = new mapboxgl.Map({
    container: 'map', // The container element where the map will be displayed
    style: 'mapbox://styles/mapbox/streets-v11', // Style of the map
    center: [73.0479, 33.6844], // Coordinates for Islamabad (longitude, latitude)
    zoom: 12 // Zoom level (adjust as needed)
});

// Optional: Add a marker at the center of the map
const marker = new mapboxgl.Marker()
    .setLngLat([73.0479, 33.6844]) // Coordinates for Islamabad
    .addTo(map);


document.addEventListener("DOMContentLoaded", () => {
  // For User Login
  const userLoginForm = document.querySelector("#userLoginForm");
  if (userLoginForm) {
      userLoginForm.addEventListener("submit", function (event) {
          event.preventDefault();
          const userID = document.querySelector("#userID").value;
          const password = document.querySelector("#password").value;

          // Simulate login process
          if (loginUser(userID, password)) {
              window.location.href = "user/dashboard.html";
          } else {
              alert("Invalid user ID or password.");
          }
      });
  }

  // For Driver Login
  const driverLoginForm = document.querySelector("#driverLoginForm");
  if (driverLoginForm) {
      driverLoginForm.addEventListener("submit", function (event) {
          event.preventDefault();
          const driverID = document.querySelector("#driverID").value;
          const password = document.querySelector("#password").value;

          // Simulate login process
          if (loginDriver(driverID, password)) {
              window.location.href = "driver/dashboard.html";
          } else {
              alert("Invalid driver ID or password.");
          }
      });
  }

  // For User Registration
  const userRegisterForm = document.querySelector("#userRegisterForm");
  if (userRegisterForm) {
      userRegisterForm.addEventListener("submit", function (event) {
          event.preventDefault();
          const name = document.querySelector("#name").value;
          const phoneNumber = document.querySelector("#phoneNumber").value;
          const password = document.querySelector("#password").value;

          // Simulate user registration
          registerUser(name, phoneNumber, password);
      });
  }

  // For Driver Registration
  const driverRegisterForm = document.querySelector("#driverRegisterForm");
  if (driverRegisterForm) {
      driverRegisterForm.addEventListener("submit", function (event) {
          event.preventDefault();
          const name = document.querySelector("#name").value;
          const vehicleRegistration = document.querySelector("#vehicleRegistration").value;
          const phoneNumber = document.querySelector("#phoneNumber").value;
          const password = document.querySelector("#password").value;

          // Simulate driver registration
          registerDriver(name, vehicleRegistration, phoneNumber, password);
      });
  }

  // For Ride Request
  const rideRequestForm = document.querySelector("#rideRequestForm");
  if (rideRequestForm) {
      rideRequestForm.addEventListener("submit", function (event) {
          event.preventDefault();
          const destinationLat = document.querySelector("#destinationLat").value;
          const destinationLon = document.querySelector("#destinationLon").value;

          const paymentChoice = document.querySelector("input[name='paymentMethod']:checked").value;
          const price = calculatePrice(0, 0, destinationLat, destinationLon);  // Dummy current location (0, 0)

          // Simulate ride request
          requestRide(destinationLat, destinationLon, paymentChoice, price);
      });
  }

  // Driver dashboard: Turn on availability
  const availabilityButton = document.querySelector("#turnAvailability");
  if (availabilityButton) {
      availabilityButton.addEventListener("click", function () {
          setDriverAvailability(true);
          alert("Availability turned on.");
      });
  }

  // Driver dashboard: Receive ride request
  const receiveRequestButton = document.querySelector("#receiveRideRequest");
  if (receiveRequestButton) {
      receiveRequestButton.addEventListener("click", function () {
          const rideRequest = getNextRideRequest();  // Assume this is a global queue for requests

          if (rideRequest) {
              const accepted = acceptRide(rideRequest.id, rideRequest.lat, rideRequest.lon);
              if (accepted) {
                  completeRide(rideRequest.id);
              } else {
                  alert("Ride not accepted.");
              }
          } else {
              alert("No ride requests available.");
          }
      });
  }
});

// Simulate login for User
function loginUser(userID, password) {
  // Replace with actual login logic connected to backend
  console.log(`User login attempt: ${userID}, ${password}`);
  // For now, just return true for demonstration
  return true;
}

// Simulate login for Driver
function loginDriver(driverID, password) {
  // Replace with actual login logic connected to backend
  console.log(`Driver login attempt: ${driverID}, ${password}`);
  // For now, just return true for demonstration
  return true;
}

// Simulate user registration
function registerUser(name, phoneNumber, password) {
  // Replace with actual registration logic
  console.log(`User registration: ${name}, ${phoneNumber}`);
  alert("User registered successfully!");
}

// Simulate driver registration
function registerDriver(name, vehicleRegistration, phoneNumber, password) {
  // Replace with actual registration logic
  console.log(`Driver registration: ${name}, ${vehicleRegistration}`);
  alert("Driver registered successfully!");
}

// Simulate calculating the price for a ride
function calculatePrice(currLat, currLon, destLat, destLon) {
  // For simplicity, we're returning a static price.
  // In a real scenario, the price should be calculated based on distance.
  return 15.0; // Example price
}

// Simulate ride request
function requestRide(destinationLat, destinationLon, paymentChoice, price) {
  console.log(`Ride requested to ${destinationLat}, ${destinationLon} with payment choice: ${paymentChoice}`);
  if (paymentChoice === "1") {
      // Handle in-app payment
      alert(`Payment of $${price} processed via In-app Payment.`);
  } else {
      // Handle cash payment
      alert("Cash payment selected. Please pay the driver directly.");
  }
}

// Simulate setting driver availability
function setDriverAvailability(isAvailable) {
  // Simulate setting the availability of the driver
  console.log(`Driver availability: ${isAvailable ? "On" : "Off"}`);
}

// Simulate getting the next ride request from the queue
function getNextRideRequest() {
  // This is a dummy request, in a real scenario, this would come from the ride queue
  return { id: 1, lat: 12.9716, lon: 77.5946 };  // Example coordinates for Bangalore, India
}

// Simulate accepting a ride request
function acceptRide(rideID, lat, lon) {
  console.log(`Accepting ride request ID: ${rideID} at coordinates: ${lat}, ${lon}`);
  // Return true for successful acceptance
  return true;
}

// Simulate completing a ride
function completeRide(rideID) {
  console.log(`Ride completed for ID: ${rideID}`);
  alert("Ride completed!");
}
