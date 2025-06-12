import { View, Text, StyleSheet, TouchableOpacity, Alert } from 'react-native'
import React from 'react'
import Image from '../assets/constants/image'
import BackButton from '../assets/images/BackButton'
import { router } from 'expo-router'
import { useGlobalContext } from '../global/globalcontext'

const PayButton = ({title,value}) => {
  const {changeCoin,Coin,resetCart} = useGlobalContext();
  return (
    <TouchableOpacity 
      style={styles.box}
      onPress={() => {
        const newBalance = Coin - Number(value);
        if(newBalance < 0) Alert.alert(
                                    'Payment Failed',
                                    'Not enough money in your balance.')
        else
        {
            console.log(value);
            console.log(Coin);
            console.log(newBalance);
            changeCoin(-Number(value));
            resetCart();
            router.push('/');
        }
      }}
      activeOpacity={0.8}
    >
      <Text style={styles.title}>{title}</Text>

    </TouchableOpacity>
  )
}

export default PayButton

const styles = StyleSheet.create({
  box : {
    backgroundColor:'#1c085d',
    padding:10,
    display:'flex',
    flexDirection:'row',
    // marginTop:170,
    margin:15,
    borderRadius:10,
    alignItems:'center',
    justifyContent:'center',
    gap:10,
    height:50,
    width:'auto',
  },

  title : {
    color:'white',
    fontWeight:'bold'
  }
})