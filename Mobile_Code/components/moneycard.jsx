import { View, Text, Image, StyleSheet, TouchableOpacity } from 'react-native'
import React from 'react'
import { router } from 'expo-router'

const MoneyCard = ({ product, isSelected, onSelect }) => {
  const { id, name, image, price } = product

  return (
    <TouchableOpacity
      style={[styles.box, isSelected && styles.selectedBox]}
      onPress={onSelect}
    >
      <Image source={image} style={styles.imageThing} resizeMode='contain' />
      <Text style={styles.titleTxt} numberOfLines={3}>{name}</Text>
      <Text>{price}</Text>
    </TouchableOpacity>
  )
}


export default MoneyCard

const styles = StyleSheet.create({
  selectedBox: {
    borderWidth: 2,
    borderColor: '#1c085d',
  },
  box:{
    backgroundColor:'white',
    height:140,
    width:110,
    display:'flex',
    flexDirection:'column',
    alignItems:'center',
    justifyContent:'center',
    padding:10,
    marginVertical:15,
    marginRight:10,
    borderRadius:10,
    elevation:10,
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 10 },
    shadowOpacity: 0.23, 
    shadowRadius: 10, 


  },
  titleTxt :{
    fontWeight:'bold',
    fontSize:17
  },
  imageThing:{
    width:100,
    height:100
  }
})