import { View, Text, StyleSheet, FlatList, Image, TouchableOpacity, RefreshControl, ActivityIndicator, Modal, BackHandler, Alert} from 'react-native'
import React, { useEffect, useRef, useState } from 'react'
import { SafeAreaView } from 'react-native-safe-area-context'
import ProductButton from '../components/productbutton'
import image from '../assets/constants/image'
import ProductCard from '../components/productcard'
import EmptyState from '../components/emptystate'
import GridViewIcon from '../assets/images/GridViewIcon'
import { router } from 'expo-router'
import ListViewIcon from '../assets/images/ListViewIcon'
import HorizontalCard from '../components/horizontalcard'
import SearchInput from '../components/searchinput'
import { useQueries, useQuery } from '@tanstack/react-query'
import {getIndividualProduct, getProduct} from '../library/fetch'
import { useGlobalContext } from '../global/globalcontext'
import { WebView } from 'react-native-webview';




const App = () => {
  const [productData, setProductData] = useState(null);

  const [qrResult, setQrResult] = useState('');

  const {Coin,addToCart,getCart,Cart} = useGlobalContext();

  const quantityMap = {};
  getCart().forEach(id => {
    quantityMap[id] = (quantityMap[id] || 0) + 1;
  });

  const uniqueIds = [...new Set(getCart())];

  const productQueries = useQueries({
    queries: uniqueIds.map(id => ({
      queryKey: ['product', id],
      queryFn: () => getIndividualProduct(id),
    })),
  });


  const [modalVisible, setModalVisible] = useState(false)
   const isLoading = productQueries.some(q => q.isLoading);
  const isError   = productQueries.some(q => q.isError);
  const fetchData = productQueries.map(q => q.data).filter(Boolean);

  // const [refreshing, setRefreshing] = useState(false);
  const refetchAll = () => Promise.all(productQueries.map(q => q.refetch()));

  // if (isError) {
  //   return <Text>Error</Text>
  // }

  // const fetchData = data

  const [Grid, setGrid] = useState(false)
  const [Refreshing, setRefreshing] = useState(false)


  const onRefresh = async () => {
    setRefreshing(true);

    await refetch();

    setRefreshing(false);
    
  }

const [scanEnabled, setScanEnabled] = useState(true);
  const timerRef = useRef(null);

  const handleMessage = (event) => {
    const result = event.nativeEvent.data;

    // If we’re in the cooldown period, ignore
    if (!scanEnabled) return;
    if(result.trim() === "") return
      console.log('QR code result:', result);

    // Process this scan
    addToCart(result.trim());
    setScanEnabled(false);

    console.log(getCart());

    // Start a 5s timer to re-enable scanning
    timerRef.current = setTimeout(() => {
      setScanEnabled(true);
    }, 5000);
  };


  React.useEffect(() => {
    return () => {
      if (timerRef.current) clearTimeout(timerRef.current);
    };
  }, []);

  // useEffect(() => {
    
  //   const backAction = () => {
  //     setModalVisible(true); 
  //     return true; 
  //   };

  //   const backHandler = BackHandler.addEventListener(
  //     'hardwareBackPress',
  //     backAction
  //   );


  //   return () => backHandler.remove();
  // }, []);

  
  return (
    <SafeAreaView style={styles.safeArea}>
        

        <View style={styles.headerArea}>
          <Modal
            visible={modalVisible}
            transparent={true}>
            <View style={styles.modal}>
              <View style={styles.modalInside}>
                <Text style={styles.ask}>Are you sure you want to close SwiftCart?</Text>
                <View style={styles.optionFlex}>
                  <TouchableOpacity 
                    style={styles.touchableOption}
                    onPress={() => {BackHandler.exitApp()}}>
                      <Text style={styles.ansAsk}>Yes</Text>
                  </TouchableOpacity>

                  <TouchableOpacity 
                    style={styles.touchableOption}
                    onPress={() => {setModalVisible(false)}}>
                      <Text style={styles.ansAsk}>No</Text>
                  </TouchableOpacity>
                </View>
                
              </View>
            </View>
          
          </Modal>
          <Text style={styles.welcomeTxt}>Welcome Back,</Text>
          <Text style={styles.userTxt}>User</Text>
          

          <View style={styles.boxCoin}>
            <Text numberOfLines={1} style={styles.textCoin}>Rp {Coin}</Text>
            <Text style={styles.coin}>My Wallet</Text>
          </View>

          <TouchableOpacity 
            style={styles.egg}
            onPress={() => {router.push('/game')}}
            activeOpacity={0.6}
          >
            <Image 
              source={require('../assets/images/wallet.png')} 
              style={{ width: 50, height: 50 }} 
              resizeMode="contain"
            />

          </TouchableOpacity>
          
        </View>

        <View style={styles.flatListView}>

      
          <FlatList
            style={styles.bigList}
            data={fetchData}
            numColumns={1} 
            key={'L'} 
            keyExtractor={(item) => item.id.toString()}
            renderItem={({ item }) => <HorizontalCard product={item} quantity={quantityMap[item.id]} />}
            ListHeaderComponent={() => (
              <View style={styles.topPart}>
                <Text style={styles.bigTxt}>Your Cart</Text>

              </View>
            )}
            ListEmptyComponent={() => {
              return isLoading? (<ActivityIndicator size="large" color="#0000ff" animating={true}/>) : (<EmptyState title="No Product Available" />)
            }}
            refreshControl={
              <RefreshControl refreshing={Refreshing} onRefresh={onRefresh} />
            }


          />
        </View>
            
        <View style={styles.camera}>

        <WebView
          source={{ uri: 'http://192.168.1.100' }}
          style={{ flex: 1 }}
          onMessage={handleMessage}
        />
        </View>
        <View style={styles.nextButton}>
          <ProductButton title="Next"/>
        </View>   

    </SafeAreaView>
  )
}

export default App

const styles = StyleSheet.create({
  nextButton : {
    marginLeft:10
  },
  camera : {
    backgroundColor:'white',
    display:'flex',
    height:200,
    margin:15
  },
  welcomeTxt : {
    fontWeight:'bold',
    color:'white',
  },
  userTxt : {
    fontWeight:'bold',
    color:'white',
    fontSize:30,
  },
  flatListView :{
    flex:1

  },


  touchableOption : {
    display:'flex',
    justifyContent:'center',
    alignItems:'center',
  },
  optionFlex :{
    display:'flex',
    flexDirection:'row',
    alignItems:'space-between',
    justifyContent:'space-around',
    marginTop : 20,


  },
  ansAsk : {
    fontSize:18,
    alignItems:'center',
    justifyContent:'center',
  },
  ask :{
    fontSize:20,
    fontWeight:'bold'
  },
  modalInside :{
    width:250,
    height:125,
    paddingHorizontal: 15,
    paddingVertical : 10,
    backgroundColor: 'white',
    borderRadius:10,
    elevation:10,
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 10 },
    shadowOpacity: 0.23, 
    shadowRadius: 10, 
  },
  modal :{
    alignItems:'center',
    justifyContent:'center',
    flex: 1,
    backgroundColor:'rgba(0, 0, 0, 0.4)'
  },
  safeArea : {
    height:'100%',
    backgroundColor: '#1C085D',
    flex: 1
  },
  headerArea : {
    backgroundColor: '#1C085D',
    padding: 10
  },
  bigList : {
    backgroundColor:'white',
    borderRadius:10,
    padding:20,
    borderBottomLeftRadius:0,
    borderBottomRightRadius:0,
    paddingBottom:10,

  },
  bigTxt : {
    fontSize:30,
    fontWeight: 'bold',
  },
  topPart : {
    display:'flex',
    flexDirection:'row',
    alignItems:'center',
    justifyContent:'space-between',
    margin:0,

  },
  boxCoin : {
    position:'absolute',
    backgroundColor:'white',
    top :40,
    left:200,
    zIndex: 5,
    borderRadius:10,
    paddingHorizontal: 15,
    paddingVertical:8,
    alignItems:'flex-start',
    elevation: 10,
    shadowColor: '#000', 
    shadowOffset: { width: 0, height: 10 },
    shadowOpacity: 0.23, 
    shadowRadius: 10,
    width:170,

  },
  textCoin:{
    fontSize:25,
    fontWeight:'900',
    color:'#1C085D'
  },
  coin : {
    color:'gray'
  },
  egg :{
    position:'absolute',
    width:60,
    height:60,
    left:300,
    top:700,
    zIndex:5,
    backgroundColor:'white',
    borderRadius:'50%',
    alignItems:'center',
    justifyContent:'center',
    elevation:10,
    shadowColor: '#000', 
    shadowOffset: { width: 0, height: 10 },
    shadowOpacity: 0.23, 
    shadowRadius: 10,
  },
  fullEgg : {
    width:28,
    height:35,
  }
});