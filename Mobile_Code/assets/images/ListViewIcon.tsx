import * as React from "react";
import Svg, { Path } from "react-native-svg";

const ListViewIcon = (props: any) => (
  <Svg xmlns="http://www.w3.org/2000/svg" height={24} width={24} viewBox="0 0 48 48" {...props}>
    <Path d="M6 38V10h36v28Zm3-19.65h5.3V13H9Zm8.3 0H39V13H17.3Zm0 8.3H39v-5.3H17.3Zm0 8.35H39v-5.35H17.3ZM9 35h5.3v-5.35H9Zm0-8.35h5.3v-5.3H9Z" />
  </Svg>
);

export default ListViewIcon;
