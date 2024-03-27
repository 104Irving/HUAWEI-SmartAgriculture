//显示该农田某一项数据具体信息及时间轴图标的页面
import router from '@ohos.router'
import {McLineChart, Options} from '@mcui/mccharts'

interface ChartItem{
  ItemName:string
  //需要变量的数据表,需要联网获得
}

@Entry
@Component
struct DetailChart{
  @State ChartItemList: ChartItem[] = [
    {ItemName:'温度'},
    {ItemName:'空气湿度'},
    {ItemName:'二氧化碳'},
    {ItemName:'光照'},
    {ItemName:'土壤湿度'},
  ]
  @State ChartItemShowList:boolean[] = [false, false, false, false, false]

  //测试用数据图标
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
      }
    ]
  })

  //数据图标的更新
  aboutToAppear(){
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

  //呈现数据图表的函数
  @Builder
  ListItemShow(index:number){
    Column(){
      Row(){
        Text(this.ChartItemList[index].ItemName)
          .fontSize(30)
      }.width("100%")

      if(this.ChartItemShowList[index]){
        Column(){McLineChart({options: this.seriesOption})}
        .width('100%')
        .height('50%')
        .transition({type:TransitionType.All, opacity:0,translate: { x: 0, y: -200 }})
      }
    }
  }

  build(){
    Column(){
      Text("详细详细")
        .fontSize(30)
      List({space:8}){
        ForEach(this.ChartItemList, (Item: ChartItem, index:number) => {
          ListItem() {
            this.ListItemShow(index)
          }
          .backgroundColor("#ffffff")
          .onClick(()=>{
            animateTo({duration: 650, curve: Curve.Smooth},
              () => {this.ChartItemShowList[index] = !this.ChartItemShowList[index]})
          })
        })
      }
      .height("100%")
    }
    .width('100%')
    .height('100%')
    .backgroundColor("#ffe9e9e9")
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


