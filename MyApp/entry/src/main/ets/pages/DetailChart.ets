//显示该农田某一项数据具体信息及时间轴图标的页面
import router from '@ohos.router'
import {McLineChart, Options} from '@mcui/mccharts'


@Entry
@Component
struct DetailChart{

  ElementList: string[] = [
    '温度','空气湿度','二氧化碳','光照','土壤湿度'
  ]
  @State name:string = '';
  @State seriesOption: Options = new Options({
    xAxis:{
      data:['周一','周二','周三','周四','周五','周六','周日']
    },
    yAxis:{
      name:'温度'
    },
    series:[
      {
        name:'最高气温',
        data:[11, 11, 15, 13, 12, 13, 10]
      },
      {
        name:'最低气温',
        data:[1, -2, 2, 5, 3, 2, 0]
      }
    ]
  })


  aboutToAppear(){
    this.name = router.getParams()?.['name']
    console.log(this.name)
    // setTimeout(() => {
    //   // 传递需要修改的属性与数值，不需要全部传
    //   this.seriesOption.setVal({
    //     series:[
    //       {
    //         name:'最高气温',
    //         data:[110, 110, 150, 130, 120, 190, 100]
    //       },
    //     {
    //     name:'最低气温',
    //     data:[1, -20, 2, 5, 3, 2, 0]
    //   }
    //     ]
    //   })
    // }, 2000)
  }

  build(){
    Column(){
      Tabs(){

      }
    }
    //   //顶部栏
    //   Row({space: 50}) {
    //     //返回键
    //     Text(`<`)
    //       .fontSize(40)
    //       .fontWeight(FontWeight.Bold)
    //       .onClick(()=>{
    //         router.back()
    //       })
    //     Text(this.name)
    //       .fontSize(30)
    //   }
    //   .width('95%')
    //
    //   Column(){
    //     McLineChart({
    //       options: this.seriesOption
    //     })
    //   }
    //   .width('100%')
    //   .height('50%')
    //   .backgroundColor('#ffe5fca7')
    //
    //   Text('其他部分')
    //     .fontSize(30)
    //     .textAlign(TextAlign.Center)
    // }
  }
}


