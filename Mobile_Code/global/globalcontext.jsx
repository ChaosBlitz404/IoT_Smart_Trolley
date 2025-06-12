import { createContext, useContext, useState } from "react";

const GlobalContext = createContext()

export const useGlobalContext = () => useContext(GlobalContext)

const CoinSystem = ({children}) =>{

    const [Coin, setCoin] = useState(0)
    const [Cart, setCart] = useState(['PR005','PR005'])



    const changeCoin = (value) => {
        setCoin(prev => prev + value);
    }

    const addToCart = (item) => {
        setCart((prevCart) => [...prevCart, item]);
    }

    const removeFromCart = (item) => {
        const index = Cart.findIndex(cartItem => cartItem.id === item.id);
        if (index > -1) {
            const newCart = [...Cart];
            newCart.splice(index, 1); 
            setCart(newCart);
        }
    };

    const isInCart = (id) => {
        return Cart.some(item => item.id === id)
    }

    const getCart = () =>{
        return Cart
    }

    const resetCart = () => {
        setCart([]);
    }



    

    return (
        <GlobalContext.Provider value={{Coin,Cart,changeCoin,addToCart,removeFromCart,isInCart,getCart,resetCart}}>
            {children}
        </GlobalContext.Provider>

    );

}

export default CoinSystem;