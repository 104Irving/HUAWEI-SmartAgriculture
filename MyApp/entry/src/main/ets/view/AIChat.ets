import axios from '@ohos/axios'
import ChatModel from '../Common/Bean/ChatModel'

@Component
export default struct AIChat{
  @State ChatLog:ChatModel[] = [

  ]

  @State UserChart:string = ""
  @State AIChart:string = ""

  build(){
    Column(){
      Column(){
        Text("MiKu DaYo")
          .height("5%")

        Row(){
          Text("")
            .width("5%")

          List({space: 8}) {
            ForEach(this.ChatLog, (ChatItem:ChatModel, index:number) => {
              //FarmShow不能删除,删除会不能预览
              ListItem() {
                Column(){
                  Text(ChatItem.Content)
                    .fontSize(25)
                    .padding(20)
                    .copyOption(CopyOptions.InApp)
                }
                .width("100%")
              }
              .margin(10)
              .backgroundColor(ChatItem.IfAI?"#006eee":"#ffee5f00")
              .onClick(()=>{
              })
            })
          }
          .height('80%')
          .width("80%")
          .listDirection(Axis.Vertical) //列表垂直方向布局
          .scrollBar(BarState.Auto)


        }
        TextInput({placeholder:'来跟AI聊聊天吧'})
          .type(InputType.Normal)
          .onChange((value) =>{
            this.UserChart = value
          })
          .transition({ type: TransitionType.All, opacity: 0})

        Button('发送')
          .width('95%')
          .margin({top:10})
          .backgroundColor(Color.Blue)
          .onClick(() =>{
            axios({
              url:'http://127.0.0.1:5000/ZHIPU',
              params:{
                str:this.UserChart
              }
            }).then(res=>{
              this.AIChart=res.data
              this.ChatLog.push(new ChatModel(this.UserChart, false))
              this.ChatLog.push(new ChatModel(this.AIChart, true))
              console.log(this.AIChart)
            })
          })

      }
      .width("100%")
      .justifyContent(FlexAlign.SpaceEvenly)
    }
  }

}