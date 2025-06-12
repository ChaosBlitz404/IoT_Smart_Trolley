import { View, Text, StyleSheet, TouchableOpacity } from 'react-native'
import React from 'react'
import Image from '../assets/constants/image'
import BackButton from '../assets/images/BackButton'
import { router } from 'expo-router'

const ProductButton = ({title}) => {
  return (
    <TouchableOpacity 
      style={styles.box}
      onPress={() => {router.push('/cart')}}
      activeOpacity={0.8}
    >
      <Text>{title}</Text>
      <BackButton/>
    </TouchableOpacity>
  )
}

export default ProductButton

const styles = StyleSheet.create({
  box : {
    backgroundColor:'white',
    padding:10,
    display:'flex',
    flexDirection:'row',
    margin:5,
    borderRadius:10,
    alignItems:'center',
    justifyContent:'center',
    gap:10,
    width:150,
  }
})