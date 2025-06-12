import { View, Text, ScrollView, StyleSheet, Image, TouchableOpacity, Animated, TextInput, FlatList } from 'react-native'
import React, { useState } from 'react'
import { SafeAreaView } from 'react-native-safe-area-context'
import image from '../../assets/constants/image'
import { useGlobalContext } from '../../global/globalcontext'
import MoneyCard from '../../components/moneycard'
import ProductButton from '../../components/productbutton'
import ConfirmButton from '../../components/confirmbutton'

const Game = () => {

  const [Luck, setLuck] = useState(0)
  const [coinPosition] = useState(new Animated.Value(0))
  const {changeCoin} = useGlobalContext()
  const [shakeAnimation] = useState(new Animated.Value(0))
  const [isButtonDisabled, setIsButtonDisabled] = useState(false)

  const fetchData = [
    { id: 1, name: 'Rp10.000', value: 10000, image: require('../../assets/images/1stMoney.png') },
    { id: 2, name: 'Rp25.000', value: 25000, image: require('../../assets/images/2ndMoney.png') },
    { id: 3, name: 'Rp50.000', value: 50000, image: require('../../assets/images/3rdMoney.png') },
    { id: 4, name: 'Rp100.000', value: 100000, image: require('../../assets/images/4thMoney.png') },
    { id: 5, name: 'Rp250.000', value: 250000, image: require('../../assets/images/5thMoney.png') },
    { id: 6, name: 'Rp500.000', value: 500000, image: require('../../assets/images/6thMoney.png') },
  ];

  const [selectedCardId, setSelectedCardId] = useState(null)

  const handleSelectCard = (id) => {
    setSelectedCardId(id)
  }
  const [text, setText] = useState('');
  

  return (
    <SafeAreaView style={styles.fullArea}>
      <View style={styles.viewList}>
          <FlatList
              style={styles.moneyList}
              contentContainerStyle={styles.contentMoney}
              data={fetchData}
              numColumns={3}
              key={'G'} 
              keyExtractor={(item) => item.id.toString()}
              renderItem={({ item }) => <MoneyCard product={item} isSelected={selectedCardId === item.id} onSelect={() => handleSelectCard(item.id)}/>}
              ListHeaderComponent={() => (
                <Text style={styles.headerTxt}>Choose An Amount</Text>
              )}
            />
      </View>
        
      <View style={styles.typeAmount}>
          <Text style={styles.typeTxt}>Or Type an Amount: </Text>
          <View style={styles.inputRow}>
            <Text style={styles.rpPrefix}>Rp</Text>
            <TextInput
                style={styles.txtInput}
                placeholder='Enter Amount'
                keyboardType='numeric'
                onChangeText={(text) => {
                  setSelectedCardId(null)
                  setText(text);
                }}
            />
          </View>
      </View>
          <ConfirmButton style={styles.next} title='Confirm' 
          value={
            text ? parseInt(text.trim()) : 
            (selectedCardId ? 
            fetchData.find(item => item.id === selectedCardId).value : 0)
          }/>
    </SafeAreaView>
  )
}

export default Game

const styles = StyleSheet.create({
  inputRow: {
    display:'flex',
    marginTop:10,
    flexDirection: 'row',
    alignItems: 'center',
    backgroundColor: 'white',
    borderRadius: 10,
    paddingHorizontal: 10,
    elevation: 3,
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 4 },
    shadowOpacity: 0.1,
    shadowRadius: 6,
    marginBottom: 10,
    height: 50,
    width:150,
},
rpPrefix: {
  fontSize: 16,
  fontWeight: 'bold',
  marginRight: 5,
  color: '#333',
},

  txtInput: {
    flex: 1,
    // textAlign:'center',
    fontSize: 16,
  },
  typeTxt : {
    fontWeight:'bold'
  },
  textInput : {
    backgroundColor:'white',
    height:50,
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
  typeAmount : {
    display:'flex',
    alignItems:'center'
  },
  viewList : {
    height:370,
    marginTop:10,
  },
  contentMoney:{
    alignItems:'center',
    maxHeight: 300,
  },
  headerTxt:{
    textAlign:'center',
    fontSize:20,
    fontWeight:'bold'
  },
  moneyList :{
    display:'flex',
  },

  
})