// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
import { getFirestore } from "firebase/firestore"; // ← Firestore import
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyCK82DyvaSCPqRq8IaVQDZUtcJrLEIDSh0",
  authDomain: "swiftcart-6a723.firebaseapp.com",
  projectId: "swiftcart-6a723",
  storageBucket: "swiftcart-6a723.firebasestorage.app",
  messagingSenderId: "422308560962",
  appId: "1:422308560962:web:d855d884b3f76daeac2ddb",
  measurementId: "G-DHD712Y7QD"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);
const firestore = getFirestore(app);

export { app, firestore, analytics };