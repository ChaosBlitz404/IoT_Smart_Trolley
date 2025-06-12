import { View, Text, ScrollView, StyleSheet, Image, TouchableOpacity, ActivityIndicator, Alert, Animated, Modal } from 'react-native'
import React, { useEffect, useState } from 'react'
import { SafeAreaView } from 'react-native-safe-area-context'
import CustomButton from '../../components/custombutton'
import { useQuery } from '@tanstack/react-query'
import {getIndividualProduct} from '../../library/fetch'
import { router, useLocalSearchParams } from 'expo-router'
import { useGlobalContext } from '../../global/globalcontext'
import CloseButton from '../../assets/images/CloseButton'

const Item = () => {
  const {id} = useLocalSearchParams()

  const {data,isLoading, isError, error, refetch  } = useQuery({
    queryKey: ['productIndividual',id],
    queryFn: () => getIndividualProduct(id)});
    const [isZoomed, setIsZoomed] = useState(false)

    useEffect( () =>{
      console.log(data)
    },[data])

  const {Coin,addToCart,removeFromCart,isInCart,changeCoin} = useGlobalContext()
  

  //fetching data by id
    if(isLoading){
      return <ActivityIndicator/>
    }
  
  const {title,price,description,image} = data //|| {"id":2,"title":"Mens Casual Premium Slim Fit T-Shirts ","price":22.3,"description":"Slim-fitting style, contrast raglan long sleeve, three-button henley placket, light weight & soft fabric for breathable and comfortable wearing. And Solid stitched shirts with round neck made for durability and a great fit for casual fashion wear and diehard baseball fans. The Henley style round neckline includes a three-button placket.","category":"men's clothing","image":"https://fakestoreapi.com/img/71-3HjGNDUL._AC_SY879._SX._UX._SY._UY_.jpg","rating":{"rate":4.1,"count":259}}


  // console.log("Incoming Data")
  // console.log(data)

  return (
    <SafeAreaView style={styles.area}>

      
      <ScrollView>



        <View style={styles.bigContainer}>
        <Modal
            visible={isZoomed}
            transparent={true}>
            <View style={styles.modal}>
              <View style={styles.modalInside}>
                  <TouchableOpacity 
                    onPress={() => setIsZoomed(false)}>
                      <CloseButton/>
                  </TouchableOpacity>
                  <Image
                    source={{uri: image}}
                    style={styles.imgFullScreen}
                    resizeMode='cover'
                  />


              </View>
                
            </View>
          
          </Modal>

          <TouchableOpacity 
            onPress={() => setIsZoomed(true)}
          >
            <Image
              source={{uri: image}}
              style={styles.img}
              resizeMode='contain'
            />
          </TouchableOpacity>

            

          <View style={styles.horizLine}></View>
          <Text style={styles.title}>{title}</Text>
          <Text style={styles.priceTitle}>Price</Text>
          <Text style={styles.actualPrice}>Rp {price}</Text>
          <Text style={styles.priceTitle}>Description</Text>
          <Text>{description}</Text>

          
  
        </View>
      </ScrollView>
    </SafeAreaView>
  )
}

export default Item

const styles = StyleSheet.create({

  imgFullScreen : {
    width:'100%',
    height:'100%'
  },
  modalInside :{
    width:'99%',
    height:500,
    backgroundColor:'white'

  },
  modal :{
    alignItems:'center',
    justifyContent:'center',
    flex: 1,
    backgroundColor:'rgba(0, 0, 0, 0.4)'
  },
  area :{
    height:'100%',
    backgroundColor:'white'
  },
  img:{
    height:250,
    width:'100%'
  },
  bigContainer:{
    display:'flex',
    flexDirection:'column',
    justifyContent:'center',
    padding:25,
  },
  horizLine :{
    height: 2,  
    backgroundColor:'black',
    marginVertical:15
  },
  title :{
    fontSize:20,
    fontWeight:'bold',
    marginBottom:15
  },
  priceTitle:{
    fontSize:15,
    fontWeight:'bold',
    marginBottom:2
  },
  actualPrice :{
    marginBottom:15
  },
  position :{
    position:'absolute',
    top:640,
    left:25,
    borderRadius:10
  },
  buyButton :{
    backgroundColor:'purple',
    elevation: 10,
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 10 },
    shadowOpacity: 0.23, 
    shadowRadius: 10, 
  },
  sellButton :{
    backgroundColor:'white',
    elevation: 5,
    shadowColor: '#000', 
    shadowOffset: { width: 0, height: 2 }, 
    shadowOpacity: 0.1, 
    shadowRadius: 5, 
  },
  sellTxt :{
    color:'purple'
  },
  buyTxt : {
    color : 'white'
  }
})