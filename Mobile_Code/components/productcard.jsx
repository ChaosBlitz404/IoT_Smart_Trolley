import { View, Text, Image, StyleSheet, TouchableOpacity } from 'react-native'
import React from 'react'
import { router } from 'expo-router'

const ProductCard = ({product}) => {

  const { id,title, image, price} = product
  return (
    <TouchableOpacity style={styles.box}
      onPress={() => router.push(`/item/${id}`)}
    >
      <Image
        source={{uri: image}}
        style={styles.imageThing}
        resizeMode='contain'
      />
      <Text style={styles.titleTxt} numberOfLines={3}>{title}</Text>
      <Text>{price}</Text>
    </TouchableOpacity>
  )
}

export default ProductCard

const styles = StyleSheet.create({
  box:{
    backgroundColor:'white',
    height:250,
    width:170,
    display:'flex',
    flexDirection:'column',
    alignItems:'flex-start',
    justifyContent:'space-between',
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