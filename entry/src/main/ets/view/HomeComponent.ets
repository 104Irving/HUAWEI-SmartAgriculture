import FarmBean from '../common/bean/FarmBean';
import MainViewModel from '../model/MainViewModel';
@Component
export default struct HomeComponent{

  @State farmBean: FarmBean = null;
  private timerId: number = 0;//计时器id，每5秒读取一次数据

  build(){
    Column({space:8}){
      Text('选择农田')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({top:10})
      Divider().width('95%')
      Row(){
        Select([
          { value: '一号田', icon: $r('app.media.leaf') },
          { value: '二号田', icon: $r('app.media.leaf') },
          { value: '三号田', icon: $r('app.media.leaf') },
          { value: '四号田', icon: $r('app.media.leaf') },
          { value: '五号田', icon: $r('app.media.leaf') }])
          .selected(0)
          .value('选择农田')
          .font({ size: 24, weight: 600 })
          .fontColor('#182431')
          .selectedOptionFont({ size: 22, weight: 600 })
          .optionFont({ size: 18, weight: 500 })

      }.width('95%')
      Divider().width('95%')
      Text('传感器数据')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({top:10})
      Divider().width('95%')

      //温度
      Row(){
        Text('温度:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        //Text('22.5°C')
        Text(`${this.farmBean.temperature}°C`)
          .fontSize(20)

      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)

      //湿度
      Row(){
        Text('空气湿度:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        //Text('56%')
        Text(`${this.farmBean.humidity}%`)
          .fontSize(20)

      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)

      //Co2浓度
      Row(){
        Text('二氧化碳:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Text(`${this.farmBean.co2}ppm`)
          .fontSize(20)

      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)

      //光照
      Row(){
        Text('光照:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Text(`${this.farmBean.lumination}Lux`)
          .fontSize(20)

      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)

      //土壤湿度
      Row(){
        Text('土壤湿度:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Text(`${this.farmBean.soilHumidity}%`)
          .fontSize(20)
      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#f1f2f3')
  }

  loadFarmData(){
    this.farmBean = MainViewModel.getFarmData(1);
  }

  aboutToAppear(){
    //当页面出现时获取设备数据
    this.loadFarmData();

    //每隔5秒加载一次数据
    this.timerId = setInterval(()=>{
      this.loadFarmData();
    },5000)
  }
}
