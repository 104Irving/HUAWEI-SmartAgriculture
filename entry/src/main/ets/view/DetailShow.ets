
import FarmBean from '../Common/Bean/Farmbean';

@Component
export default struct DetailShow{


  @State farmBean: FarmBean = null;

  build(){
    Column({space:8}){
      Divider().width('95%')
      Text('传感器数据')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({ top: 10 })
      Divider()
        .width('95%')

      this.ElementShow('温度', this.farmBean.temperature)
      this.ElementShow('空气湿度', this.farmBean.humidity)
      this.ElementShow('二氧化碳', this.farmBean.co2)
      this.ElementShow('光照', this.farmBean.lumination)
      this.ElementShow('二氧化碳', this.farmBean.co2)
      this.ElementShow('土壤湿度', this.farmBean.soilHumidity)
    }
  }
}

