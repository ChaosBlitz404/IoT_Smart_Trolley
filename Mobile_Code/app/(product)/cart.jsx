import {StyleSheet, FlatList, View, Text} from 'react-native'
import React from 'react'
import { SafeAreaView } from 'react-native-safe-area-context'
import EmptyState from '../../components/emptystate'
import HorizontalCard from '../../components/horizontalcard'
import { useGlobalContext } from '../../global/globalcontext'
import ProductButton from '../../components/productbutton'
import ConfirmButton from '../../components/confirmbutton'
import { useQueries } from '@tanstack/react-query'
import { getIndividualProduct } from '../../library/fetch'
import PayButton from '../../components/paybutton'

const Cart = () => {

  const {getCart,changeCoin} = useGlobalContext()

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

  const isLoading = productQueries.some(q => q.isLoading);
  const isError   = productQueries.some(q => q.isError);
  const fetchData = productQueries.map(q => q.data).filter(Boolean);

  const subtotal = fetchData.reduce((acc, item) => {
  const quantity = quantityMap[item.id] || 1;
    return acc + item.price * quantity;
  }, 0);

  const TAX_RATE = 0.1; 

  const tax = subtotal * TAX_RATE;
  const total = subtotal + tax;
  return (
    <SafeAreaView style={styles.safeArea}>
      
          <FlatList
            style={styles.bigList}
            data = {fetchData}

            keyExtractor = {(item) => item.id}
            renderItem = {({item}) => (
              <HorizontalCard product={item} quantity={quantityMap[item.id]}/>
            )}

            ListEmptyComponent = {() => (
              <EmptyState title="No Product Has Been Bought"/>
            )}

            ListHeaderComponent={() => (
              <View style={styles.topPart}>
              <Text style={styles.bigTxt}>Billing</Text>
            
              </View>
            )}
          />
        <View style={styles.line} />
        <View style={styles.paymoment}>
          <View style={styles.pay}>
            <Text style={styles.payTxt}>Subtotal</Text>
            <Text style={styles.payTxt}>Rp {subtotal}</Text>
          </View>
          <View style={styles.pay}>
            <Text style={styles.payTxt}>Tax</Text>
            <Text style={styles.payTxt}>Rp {tax}</Text>
          </View>
          <View style={styles.pay}>
            <Text style={styles.payTxtBold}>Total</Text>
            <Text style={styles.payTxtBold}>Rp {total}</Text>
          </View>
        </View>
        <View style={styles.nextButton}>
          <PayButton title="Check Out" value={total}/>
        </View>

          

    </SafeAreaView>
  )
}

export default Cart

const styles = StyleSheet.create({
  line: {
    borderBottomColor: '#aaa', 
    borderBottomWidth: 1,      
    marginVertical: 10,  
    marginHorizontal:20,     
  },
  payTxtBold : {
    fontSize:20,
    color:'black',
    fontWeight:'bold'
  },
  payTxt : {
    fontSize:16,
    color:'black',

  },
  pay : {
    display:'flex',
    flexDirection:'row',
    justifyContent:'space-between',

  },
  paymoment : {
    height:120,
    margin:20
  },
  safeArea : {
    height:'100%',
    backgroundColor: 'white',
  },
  headerArea : {
    backgroundColor: 'purple',
    padding: 10
  },
  bigList : {
    backgroundColor:'white',
    padding:20
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
    top :70,
    left:270,
    zIndex: 5,
    borderRadius:10,
    paddingHorizontal: 15,
    paddingVertical:8,
    alignItems:'flex-end',
    elevation: 10,
    shadowColor: '#000', 
    shadowOffset: { width: 0, height: 10 },
    shadowOpacity: 0.23, 
    shadowRadius: 10,
    width:100,

  },
  textCoin:{
    fontSize:25,
    fontWeight:'900',
    color:'purple'
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