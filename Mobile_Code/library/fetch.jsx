import { collection, doc, getDoc, getDocs } from "firebase/firestore";
import { firestore } from "../firebase/firebaseConfig";

export const getProduct = async () => {
  const productCollection = collection(firestore, "storedb"); 
  const querySnapshot = await getDocs(productCollection);

  const products = [];
  querySnapshot.forEach((doc) => {
    products.push({ id: doc.id, ...doc.data() });
  });

  return products;
};

export const getIndividualProduct = async (productId) => {
  const productRef = doc(firestore, "storedb", productId); // path: /msproduct/PR001
  const snapshot = await getDoc(productRef);

  if (snapshot.exists()) {
    return { id: snapshot.id, ...snapshot.data() };
  } else {
    throw new Error(`Product with ID ${productId} not found`);
  }
};
